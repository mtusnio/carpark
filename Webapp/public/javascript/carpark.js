var CAR_COUNT=8
var PARKING_SPACE_IMAGE="parking_available.png"
var CAR_IMAGES=5

/**
 * Returns a random integer between min (inclusive) and max (inclusive)
 * Using Math.round() will give you a non-uniform distribution!
 */
function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function getCarPicture(status) {
    if(status == 1) {
        return PARKING_SPACE_IMAGE;
    }

    return "car" + getRandomInt(1, CAR_IMAGES) + ".png";
}

function updateAllCars() {
    $.getJSON("/carpark/cars/1/" + CAR_COUNT, function(data) {
        for(var i = 0; i < data.length; i++) {
            var carTag = "#car" + data[i].id;
            if(data[i].status == 0 && !$(carTag).attr("src").includes(PARKING_SPACE_IMAGE)) {
                continue;
            }
            $(carTag).attr("src", "/images/carpark/" + getCarPicture(data[i].status));
        }
    });
}

$( document ).ready(function() {
   (function periodicUpdate() {
	updateAllCars();
    setTimeout(periodicUpdate, 500);
    })();
});
