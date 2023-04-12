let serialPdm;
let portName = '/dev/tty.usbmodem1301';
let sensors;
let light = false;

function setup() {
  serialPdm = new PDMSerial(portName);
  console.log(serialPdm.inData);
  sensors = serialPdm.sensorData;
  createCanvas(800,600);
}

function draw() {
  background(225);
  textSize(32);
  fill(0);

  if(sensors.a0 < 341) {
    background(0, 255, 255);
  } else if (sensors.a0 < 682) {
    background(255, 0, 255);
  } else {
    background(255);
  }
  text("pressure: " + sensors.a0, 10, 30);
  text("click = light switch", 10, 80);
}

function mouseClicked() {
  if(!light) {            // if light is off, turn it on
    serialPdm.transmit('led', 1);
    console.log(serialPdm.sensorsConnected());
    light = true;
  } else {                // if light is on, turn it off
    serialPdm.transmit('led', 0);
    light = false;
  }
}