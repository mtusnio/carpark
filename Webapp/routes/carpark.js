var express = require('express');
var execSync = require('child_process').execSync;
var StringDecoder = require('string_decoder').StringDecoder;
var router = express.Router();
var fs = require('fs');

var getCarStatus = function(carId) {
    carStatus = 1;
    path = "/var/carpark/Carpark" + carId;
    if (fs.existsSync(path)) {
        output = execSync("cat " + path);
        carStatus = parseInt(output)
    }
    return carStatus;
}

/* GET home page. */
router.get('/', function(req, res, next) {
    res.render('carpark', { title: 'Express' });
});

router.get("/car/:carId", function(req, res, next) {
    carId = req.params.carId;
    res.json({ id: carId, status: getCarStatus(carId) });
});

router.get("/cars/:carStart/:carEnd", function(req, res, next) {
    carStart = req.params.carStart
    carEnd = req.params.carEnd
    cars = []
    for(i = carStart; i <= carEnd; i++) {
        cars.push({id: i, status: getCarStatus(i)});
    }
    res.json(cars)
});

module.exports = router;
