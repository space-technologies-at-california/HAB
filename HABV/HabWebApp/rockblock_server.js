const express = require('express')
const bodyParser = require('body-parser');
const app = express()
const port = 3000

// Parse URL-encoded bodies (as sent by HTML forms), which is how we get out data from Iridium
app.use(bodyParser.urlencoded({ extended: true }));

// Home endpoint
app.get('/', (req, res) => {
    res.send("Hello, World!")
})

// Handing the Rockblock POST req
app.post('/rockblock-data', (req, res) => {
    res.sendStatus(200)        // Notifying Iridium that we've successfully received their request.           
    processData(req.body.data)
})

// We can write code to store and process the data within this function.
function processData(data) {
    rockblockData = 
    console.log('Got body:', req.body);
}

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})