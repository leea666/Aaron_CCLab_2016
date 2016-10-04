//AIzaSyDi-2HjJxTMSYCbdT9MJH8_j6inGUlWM28
//https://maps.googleapis.com/maps/api/js?key=AIzaSyDi-2HjJxTMSYCbdT9MJH8_j6inGUlWM28&callback=initMap
// -34.397, 150.644
var latitude = 40.7829;
var longitude = -73.9654 ;
var map;
var place = {lat: latitude, lng: longitude} ;


//got this code from https://developers.google.com/maps/documentation/javascript/tutorial
var initMap = function() {
    map = new google.maps.Map(document.getElementById('map'), {
       center: place,
       zoom: 8
    });
 }

function getCoordinates() {
    // document.getElementById("frm1").submit();
    latitude = parseFloat(document.getElementById('input1').value) ;
    console.log(latitude) ;
    longitude = parseFloat(document.getElementById('input2').value) ;
    console.log(longitude) ;
    place = {lat: latitude, lng: longitude} ;
    initMap() ;
}

$(document).ready(function() {
	console.log("ready!") ;
});
