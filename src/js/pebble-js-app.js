var locationOptions = { "timeout": 15000, "maximumAge": 60000 }; 
var lastPos = {latitude: 0, longitude: 0};

function distance2(start, end) {
	var R = 6371; // km
	var d = Math.acos(Math.sin(start.latitude)*Math.sin(end.latitude) + 
	                  Math.cos(start.latitude)*Math.cos(end.latitude) *
	                  Math.cos(end.longitude-start.longitude)) * R;
	return d; 
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  var dist = distance2(lastPos, coordinates);
  dist *= 1000;
  console.log("Location: " + coordinates.latitude + " " + coordinates.longitude + " Distance: " + (dist | 0) + " meter");
  lastPos = coordinates;
}

function locationError(err) {
  console.warn('location error (' + err.code + '): ' + err.message);
}



Pebble.addEventListener("ready", function(e) {
	//console.log("connect!" + e.ready);
	//locationWatcher = window.navigator.geolocation.watchPosition(locationSuccess, locationError, locationOptions);
	//console.log(e.type);
});
