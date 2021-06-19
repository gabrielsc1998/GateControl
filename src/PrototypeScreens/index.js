const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

const cors = require('cors');
app.use(cors());

const port = 3000;

app.listen(port);
console.log('\n ------ API running on port ' + port + ' ------');

let feedbackGate = 0;

app.get('/pulse', async (req, res) => {

    try {   

        feedbackGate === 1 ? feedbackGate = 0 : feedbackGate = 1;
        
        console.log('/pulse');
        return res.status(200).send();

    } catch(err) {
        return res.status(400).send({error: 'Error'});
    }
});

app.get('/feedbackGate', async (req, res) => {

    try {   

        console.log('/feedbackGate');
        return res.status(200).send({feedbackGate: feedbackGate});
        
    } catch(err) {
        return res.status(400).send({error: 'Error'});
    }
});

