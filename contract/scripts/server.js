const {add_member,check_member} = require ('./add_member.js');
 
const hostname = 'localhost';
const port = 4100;

const express = require('express');
const app = express();

async function handleIsMemberRequest(req, res) {
    const id = req.query.id; // Access the ID from the query parameter

    try {
        const check_membership = await check_member(id);
        console.log(check_membership);
        res.send(check_membership);
    } catch (error) {
        console.error('Error:', error);
        res.status(500).send('Internal Server Error');
    }
}
app.get('/ismember', handleIsMemberRequest);

app.get('', (req, res) => {
    res.send('{"response" : "I\'m alive"}');
});

app.post('', (req, res) => {
    var body = '';

    req.on('data', function (data) {
        body += data;

        // Too much POST data, kill the connection!
        // 1e6 === 1 * Math.pow(10, 6) === 1 * 1000000 ~~~ 1MB
        if (body.length > 1e6)
        req.connection.destroy();
    });

    req.on('end', function () {
        res.statusCode = 200;

        const requestBody = JSON.parse(body);
        const amount = requestBody.amount;
        const customer = requestBody.customer;
        add_member(customer, amount);

        res.end(body);
    });
});

app.listen(port, hostname, () => {
    console.log(`Server running at http://${hostname}:${port}/`);
});

// GET http://localhost:4100/ismember?id=ID
// GET http://localhost:4100
// POST http://localhost:4100