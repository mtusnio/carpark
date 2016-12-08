var express = require('express');
var execSync = require('child_process').execSync;
var StringDecoder = require('string_decoder').StringDecoder;
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
    res.render('carpark', { title: 'Express' });
});

router.get("/car/:carId", function(req, res, next) {
    carId = req.params.carId;
    output = execSync("awa-server-read -c Carpark" + carId + " /1337/0/1");
    decoder = new StringDecoder('utf-8');
    res.json({ status: decoder.write(output).slice(-2)[0] });
});

module.exports = router;
