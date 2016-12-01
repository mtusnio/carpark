var express = require('express');
var exec = require('child_process').exec;
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('relay', { title: 'Express' });
});

router.get('/toggle', function(req, res, next) {
  exec("awa-server-read -q -c Relay /3306/0/5850", function(error, stdout, stderr) {
	console.log("Read was run, output: " + stdout + " error: " + stderr);
	var newWrite = "True";
  	if(stdout.includes(newWrite))
		newWrite = "False";
	console.log("Write done: " + newWrite);
	exec("awa-server-write -c Relay /3306/0/5850=" + newWrite, function(error, stdout, stderr) {
		console.log("Write was run, stdout: " + stdout + " error: " + stderr);
	});
  });
  res.render('relay', { title: 'Express' });
});

module.exports = router;
