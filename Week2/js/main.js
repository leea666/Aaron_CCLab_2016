var slideIndex = 1;
showSlide(slideIndex);

function switchSlide(n) {
  showSlide(slideIndex += n);
}

function currentSlide(n) {
  showSlide(slideIndex = n);
}

function showSlide(n) {
    var i;
    var slidesArray = document.getElementsByClassName("slides");
    var dotsArray = document.getElementsByClassName("myDot");

    if (n > slidesArray.length) {
        slideIndex = 1
    }

    if (n < 1) {
        slideIndex = slidesArray.length
    };

    for (i = 0; i < slidesArray.length; i++) {
       slidesArray[i].className = slidesArray[i].className.replace(" fadeImage", "");
    }

    for (i = 0; i < dotsArray.length; i++) {
       dotsArray[i].className = dotsArray[i].className.replace(" dot-filled", "");
    }
    slidesArray[slideIndex-1].className += " fadeImage";
    dotsArray[slideIndex-1].className += " dot-filled";
}

window.setInterval(function(){
    switchSlide(1)
}, 5000);

$(document).ready(function() {
    console.log("ready!") ;
});