// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

'use strict';

const Protocol = require('azure-iot-device-mqtt').Mqtt;
const Client = require('azure-iot-device').Client;
const Message = require('azure-iot-device').Message;
const fetch = require('node-fetch');

const deviceConnectionString = process.env.DEVICE_CONNECTION_STRING;
let sendInterval;

function disconnectHandler () {
  clearInterval(sendInterval);
  client.removeAllListeners();
  client.open().catch((err) => {
    console.error(err.message);
  });
}

function messageHandler (msg) {
  console.log('Id: ' + msg.messageId + ' Body: ' + msg.data);
  client.complete(msg, printResultFor('completed'));
}

function errorCallback (err) {
  console.error(err.message);
}

function connectCallback () {
  console.log('Client connected!');
  
  // Create a message and send it to the IoT Hub every two seconds
  sendInterval = setInterval(() => {
    const url = 'http://api.openweathermap.org/data/2.5/weather?zip=49685,us&appid=49058b1a62c960681a67da385d914a27';
    
    return fetch(url).then(res => res.json()).then(response => {
      const temp = (response.main.temp - 273.15) * 9/5 + 32;  
      const data = JSON.stringify({ DeviceType: 'WeatherSensor', temperature: temp, humidity: response.main.humidity, pressure: response.main.pressure });
      const message = new Message(data);
    
      message.properties.add('temperatureAlert', 'false');
      message.contentType = "application/json";
      message.contentEncoding = "utf-8";

      console.log(message);
           
      console.log('Sending message: start');    
      client.sendEvent(message, printResultFor('send'));
      console.log('Sending message: done')
    });  
  }, 5000);
}

// fromConnectionString must specify a transport constructor, coming from any transport package.
let client = Client.fromConnectionString(deviceConnectionString, Protocol);

client.on('connect', connectCallback);
client.on('error', errorCallback);
client.on('disconnect', disconnectHandler);
client.on('message', messageHandler);

client.open().catch(err => {
  console.error('Could not connect: ' + err.message);
});

// Helper function to print results in the console
function printResultFor(op) {
  return function printResult(err, res) {
    if (err) console.log(op + ' error: ' + err.toString());
    if (res) console.log(op + ' status: ' + res.constructor.name);
  };
}