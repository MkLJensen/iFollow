/********* Open/require libraries  *********/
var http = require('http').createServer(HTTPHandler); // Require http server and set connection cb-function: handler()
const fs = require('fs'); 							// Require filesystem module
var io = require('socket.io')(http)					// Require socket.io for server
const spi = require('spi-device');					// Require spi-device for communication with PSoC
const spi_speed = 1000000;							// Constant SPI-Speed 10MHz atm
var mysql = require('mysql');						// Require mysql for connecting and pulling data from SQL-server
const time_delay = 1000;							// Constant time-delay for timed update function
var Gpio = require('onoff').Gpio;					// Require GPIO for access to RPI-GPIO ports
var LED1 = new Gpio(26, 'out');						// GPIO handler for LED1
var LED2 = new Gpio(20, 'out');						// GPIO handler for LED2
var LED3 = new Gpio(21, 'out');						// GPIO handler for LED3
var control_on = false;								// Boolean for keeping track of control-panel status

/***************************************************
*		     MAIN CALLS		           *
****************************************************/

/* Open SPI on port 0 and save SpiObject in SPI0 */
const SPI0 = spi.open(0,0, (err) => {
	/*Send test message when opening SPI-port on 0*/
        const message = [{
                sendBuffer: Buffer.from([0x00]),
                receiveBuffer: Buffer.alloc(1),
                byteLength: 1,
                speedHz: 20000  // spi-speed
        }];
        if (err) throw err;
})

/* Start listening for client-connections on port 8080 */
http.listen(8080);

/* Specify mysql-server */
var con = mysql.createConnection({
	host: "10.192.140.96",
	user: "SUPERUSER",
	password: "pi",
	database: "DatabaseGPS"
});

/* Connect to specifed mysql-server async with cb-function */
con.connect(function(err){
	if (err) {console.log("Cant connect to SQL with ERROR: " + err + "\n");return;}	// Display error and return
	console.log("Connected to SQL-server!\n"); // Succesfull connection!
});

/* Bind events when socket are connected to client */
io.sockets.on('connection', function (socket) {
	console.log("Connected to websocket with socket.io!\n"); // Display message on client connection!

	/* TODO: Was changed locally on RPI */
	socket.on('control_event', function(data) {
      	console.log("User clicked button!\n");
		setManualControl();
		toggleLED(data);
	});
	
	/* Hook custom event for controlling the robots motor */
	socket.on('motor-controls', function (data) {
		/*Call motor-controller handler*/
		handleMotorInput(data);
	});

	/* Call a function every (time_delay) seconds for updating positions and status on website */
	setInterval(function(){
		getArrayOfPositions(socket);	// Update positions from SQL-server
		updateStatusAndUptime(socket);	// Update status from PSoC
	},time_delay);
});




/***************************************************
*		     FUNCTIONS		           				*
****************************************************/
/***************************************************
* Requests permission to either turn on or off manual
* control on robot.
* @param void
* @return void
****************************************************/
function setManualControl()
{
	control_on ? spiWrite(0x63) : spiWrite(0x6f);
	control_on = !control_on;
}

/***************************************************
* Callback-function for client connections
* @param <request><result>
* @return <result>
****************************************************/
function HTTPHandler (req, res) {

	/* Read HTML-file async with cb-function */
	fs.readFile(__dirname + '/index.html', function(err, data) {

		/* CALLBACK FUNCTION AFTER FILE HAS BEEN READ */
		if (err) {
			/* Error has been detected, send 404 error to client! */
			res.writeHead(404, {'Content-Type': 'text/html'}); //display 404 on error
			return res.end("404 Not Found");
		}
		console.log("Sending HTML to client\n");
		res.writeHead(200, {'Content-Type': 'text/html'});	// Send header to Client with content-type specified
		res.write(data);	// Send html-file to Client
		return res.end();	// Response is complete

	});

};

/***************************************************
* Motorcontrol handler for determining and sending the
* correct spi-command to PSoC
* @param <motor-direction,
*        1 = UP, 2 = DOWN, 3 = LEFT, 4 = RIGHT>
* @return void
****************************************************/
function handleMotorInput(val)
{
	/* Switch on desired direction */
	switch(val){
		case 1:
			/* Forward */
			console.log("Forward! \n");
			spiWrite(0x66);	// Send f for Forward
			break;
		case 2:
			/* Backward */
            console.log("Backwards! \n");
			spiWrite(0x62);	// Send b for Backward
            break;
		case 3:
			/* Left */
            console.log("Left! \n");
			spiWrite(0x6c);	// Send l for Left
            break;
		case 4:
			/* Right */
            console.log("Right! \n");
			spiWrite(0x72);	// Send r for Right
            break;
	}
}

/***************************************************
* Used for reading LED-state on RPi (!SYNC FUNCTION!)
* @param <LED number>
* @return <Specified LED state> -1 on error
****************************************************/
function readLED(num){
	/* Switch on desired LED */
	switch(num){
		case 1:
			return LED1.readSync();
		case 2:
			return LED2.readSync();
		case 3:
			return LED3.readSync();
		default:
			return -1;
	}
}

/***************************************************
* Used for toggling LEDs on RPi (!SYNC FUNCTION!)
* @param <LED number>
* @return void
****************************************************/
function toggleLED(num){
	if (num==1) {
		if (LED1.readSync()==0) {
			LED1.writeSync(1);	
		} else {
			LED1.writeSync(0);
		}
	} else if (num==2) {
		if (LED2.readSync()==0) {
                        LED2.writeSync(1);
                } else {
                        LED2.writeSync(0);
                }
	} else if (num==3) {
		if (LED3.readSync()==0) {
                        LED3.writeSync(1);
                } else {
                        LED3.writeSync(0);
                }
	} else {
		console.log("Unrecognized LED!\n");
	}	
}

/***************************************************
* Used for transmitting messages over UART
* @param <Message>
* @return void
****************************************************/
function uartWrite(msg)
{
	/* Just write to device-file set up for UART */
	fs.appendFile('/dev/ttyAMA0',msg, function(err) {
		if (err) {return console.log(err)};
		console.log("Succesfully sent message to UART..\n");
	});
}

/***************************************************
* Used for reading messages over UART (!SYNC FUNCTION!)
* @param void
* @return <Recieved message>
****************************************************/
function uartRead()
{
	/* Just read from device-file set up for UART */
	fs.readFileSync("/dev/ttyAMA0", (err,data) => {
		if (err) throw err;
		console.log("Succesfully read file!\n")
		return data;
	});
}

/***************************************************
* Used for transmitting messages over SPI async
* @param <Single byte message>
* @return <Recieved single byte message>
****************************************************/
function spiWrite(msg)
{
	/* Make message for spi-transfer */
	const message = [{
                sendBuffer: Buffer.from([msg]),
                receiveBuffer: Buffer.alloc(1),
                byteLength: 1,
                speedHz: spi_speed  // Constant SPI-speed specified top
        }];

	/* Transfer message async */
        SPI0.transfer(message, (err, message) => {
                if (err) throw err;
		console.log("Succesfully send SPI-message");
		console.log("Recieved: " + message[0].receiveBuffer[0]);
		return message[0].receiveBuffer[0];
        });
}

/***************************************************
* Used for reading messages over UART (!SYNC FUNCTION!)
* @param void
* @return <recieved message>
****************************************************/
function spiReadSync()
{
	/* Make empty message for spi-transfer */
	const message = [{
                sendBuffer: Buffer.from([0x00]),
                receiveBuffer: Buffer.alloc(1),
                byteLength: 1,
                speedHz: spi_speed  // Constant SPI-speed specified top
        }];

	/* Sync transfer */
	var msg = SPI0.transferSync(message);
	
	return message[0].receiveBuffer[0]; // Return first byte of recieved buffer
}

/***************************************************
* Used for recieving an array of positions from 
* SQL-server and emitting them to client.
* @param <socket> (should be unique to every client!)
* @return void
****************************************************/
function getArrayOfPositions(socket)
{
	/* Make query and send */
	con.query("SELECT Latitude, Longitude FROM GPSData", function(err,res,fields){
		if (err) return 0;
		var posArray = [];
		for (var i = 0; i < res.length; i++)
		{
			//console.log("Longitude: " + res[i].Longitude + "\n");
			//console.log("Latitude: " + res[i].Latitude + "\n");
			var arr = makeDegrees(res[i].Latitude, res[i].Longitude);
			posArray.push({latitude: arr[0], longitude: arr[1]});
		}

		/* Emit to client */
		socket.emit('updatePositions',posArray);
	});
}

/***************************************************
* Used for retrieving uptime and status, and then
* emitting information to client.
* @param <client socket>
* @return void
****************************************************/
function updateStatusAndUptime(socket){
	/* Read uptime */
	var uptime = fs.readFileSync('/proc/uptime', 'utf8');	// Read in utf8-format
	var uptimes = uptime.split(" ");			// Split uptimes into two strings
	var status = "N/A";							// Set status to default value

	/* Read status and parse from Robot */
	status = parseStatus(spiReadSync());

	/* Emit updated status to client */
	socket.emit('updateStatus',uptimes[0],status);
}

/***************************************************
* Used to parse status data from robot to readable
* string.
* @param <raw status read from robot>
* @return <readable status>
****************************************************/
function parseStatus(status){
	switch(spiReadSync()){
		case 0:
			return "Off";
			break;
		case 1:
			return "Init";
			break;
		case 2:
			return "Sleep";
			break;
		case 3:
			return "Control";
			break;
		case 4:
			return "Follow";
			break;
		case 5:
			return "Fallen";
			break;
		default:
			return "N/A";
	}
}

/***************************************************
* Used for calculating latitude and longitude to
* degrees, so its compatible with Bing Maps API.
* @param <latitude><longitude>
* @return <[latitude in degrees, longitude in degrees]>
****************************************************/
function makeDegrees(lat,long)
{
    	/* LATITUDE: Split string into DMS-form */
    	var degree = parseInt(lat.substring(0,2)); // First two char should be degrees
    	var minutes = parseFloat(lat.substring(2,lat.search(","))); // Should only contain minutes not seconds

    	/* Convert latitude to +-90 degrees */
    	var templat = degree + minutes / 60;
    	templat = lat.includes("N") ? templat*1 : templat*-1;

    	/* LONGITUDE: Split string into DMS-form */
    	degree = parseInt(long.substring(0,3)); // First two char should be degrees
    	minutes = parseFloat(long.substring(3,lat.search(","))); // Should only contain minutes not seconds

    	/* Convert longitude to +-180 degrees */
    	var templong = degree + minutes / 60;
    	templong = long.includes("E") ? templong*1 : templong*-1;

    	return [templat.toFixed(8), templong.toFixed(8)];
}
