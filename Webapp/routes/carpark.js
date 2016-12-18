var express = require('express');
var execSync = require('child_process').execSync;
var StringDecoder = require('string_decoder').StringDecoder;
var router = express.Router();
var fs = require('fs');

/* GET home page. */
router.get('/', function(req, res, next) {
    res.render('carpark', { title: 'Express' });
});

router.get("/car/:carId", function(req, res, next) {
    carId = req.params.carId;
    carStatus = 1;
    path = "/var/carpark/Carpark" + carId;
    if (fs.existsSync(path)) {
        output = execSync("cat " + path);
	carStatus = parseInt(output)
    }
    res.json({ id: carId, status: carStatus });
});

module.exports = router;
