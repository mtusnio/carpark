function updateAllCars() {
    for(i = 0; i < 6; i++) {
        $.getJSON("/carpark/car/" + i, function( data ) {
            carId = data.id;
            if(data.status == 0) {
                $("#car" + carId).css("background-color", "green");
            }
            else {
                $("#car" + carId).css("background-color", "red");
            }
        });
    }
}

$( document ).ready(function() {
    updateAllCars();
});
