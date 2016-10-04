var startDegree = 0 ;
var startDegreeTwo = 0 ;
var startPlacement = 0 ;
var startPlacementTwo = 0 ;
var degreeIncrement = 0.1 ;
var timerWaitTime = 1 ;
var holding = false ;


document.addEventListener("click", function(){
	if (holding === true) {
		holding = false ;
	} else {
		holding = true ;
	}

	var parentDiv = document.getElementsByClassName("circle") ;
	var parentTwoDiv = document.getElementsByClassName("circleTwo") ;
	var parentParentDiv = document.getElementsByClassName("parenting") ;
	var parentParentTwoDiv = document.getElementsByClassName("parentingTwo") ;

	var rotateDiv = function() {
		parentDiv[0].style.transform = "rotate("+ startDegree + "deg)" ;
		parentDiv[1].style.transform = "rotate("+ startDegree + "deg)" ;
		parentDiv[2].style.transform = "rotate("+ startDegree + "deg)" ;
		parentTwoDiv[0].style.transform = "rotate("+ startDegreeTwo + "deg)" ;
		parentTwoDiv[1].style.transform = "rotate("+ startDegreeTwo + "deg)" ;
		parentTwoDiv[2].style.transform = "rotate("+ startDegreeTwo + "deg)" ;
		startDegree += degreeIncrement ;
		startDegreeTwo -= degreeIncrement ;
	}

	var moveDiv = function() {

		parentParentDiv[0].style.transform = "translateX("+startPlacement*2+"px)" ;
		parentParentDiv[1].style.transform = "translateY("+startPlacement+"px)" ;
		parentParentTwoDiv[0].style.transform = "translateX("+startPlacementTwo*2+"px)" ;
		parentParentTwoDiv[1].style.transform = "translateY("+startPlacementTwo+"px)" ;
		if(holding === true) {
			startPlacement += degreeIncrement ;
			startPlacementTwo -= degreeIncrement ;
		}
		else {
			startPlacement -= degreeIncrement ;
			startPlacementTwo += degreeIncrement ;
		}
 	}

	window.setInterval(rotateDiv, timerWaitTime) ;
	window.setInterval(moveDiv, timerWaitTime) ;
	// clearInterval() ;

	
}) ;

document.addEventListener("keydown", function(e) {
    if (e.keyCode == 65) {
      document.body.style.background = "#E0FFFF" ;
    }
 });

document.addEventListener("keyup", function(e) {
    if (e.keyCode == 65) {
      document.body.style.background = "";
    }
 });

document.addEventListener("mouseover", function(e){
	var parentDiv = document.getElementsByClassName("circle") ;
	if(isInside(e.relatedTarget, parentDiv[0])) {
		parentDiv.background = "red" ;
	}
});



