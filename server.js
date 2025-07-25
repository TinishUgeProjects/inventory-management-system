const express = require('express');
const bodyParser = require('body-parser');
const mysql = require('mysql');
const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public'));

const db = mysql.createConnection({
    host: 'localhost',
    user: 'truck_user',
    password: 'securepassword',
    database: 'inventory'
});

db.connect(err => {
    if (err) throw err;
    console.log('MySQL Connected...');
});

// Fetch the latest truck data
app.get('/fetch_latest_truck_data', (req, res) => {
    let sql = 'SELECT * FROM truck_data WHERE approved = 0 ORDER BY entry_time DESC LIMIT 1';
    db.query(sql, (err, result) => {
        if (err) throw err;
        if (result.length > 0) {
            res.json(result[0]);
        } else {
            res.status(404).send('No data found');
        }
    });
});

// Approve the truck data
app.post('/approve_truck_data', (req, res) => {
    let driverName = req.body.driver_name;
    let driverLicense = req.body.driver_license;
    let rfid = req.body.rfid;

    let sql = `UPDATE truck_data SET driver_name = ?, driver_license = ?, approved = 1 WHERE rfid = ? AND approved = 0`;
    db.query(sql, [driverName, driverLicense, rfid], (err, result) => {
        if (err) throw err;
        if (result.affectedRows > 0) {
            res.send('Data approved and saved successfully');
        } else {
            res.status(400).send('Failed to approve data');
        }
    });
});

app.listen(3000, () => {
    console.log('Server started on port 3000');
});
