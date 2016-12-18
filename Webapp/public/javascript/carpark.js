var CAR_COUNT=8

function updateAllCars() {
    $.getJSON("/carpark/cars/1/" + CAR_COUNT, function(data) {
        for(var i = 0; i < data.length; i++) {
            carId = data[i].id;
            if(data[i].status == 0) {
                $("#car" + carId).css("background-color", "green");
            }
            else {
                $("#car" + carId).css("background-color", "red");
            }

        }
    });
}

$( document ).ready(function() {
   (function periodicUpdate() {
	updateAllCars();
    setTimeout(periodicUpdate, 500);
    })();
});
