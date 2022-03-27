
var AWS = require("aws-sdk");

AWS.config.update({
    region: "us-west-1",
    endpoint: "http://dynamodb.us-west-1.amazonaws.com",
    accessKeyId: "AKIASATEZCMDTCCPQNAH",
  // secretAccessKey default can be used while using the downloadable version of DynamoDB. 
  // For security reasons, do not store AWS Credentials in your files. Use Amazon Cognito instead.
    secretAccessKey: "jmDaFzxLhOMYTXQI0PjuEx5+nW9dQlZ3bOZfrJK1"
  });

var docClient = new AWS.DynamoDB.DocumentClient();

console.log("Scanning for hab database.");

var params = {
    TableName : "hab",
    ProjectionExpression: "#dt",
    ExpressionAttributesNames: {
        // "#tm": "time",
        "#dt": "data"
    },
    
};

// docClient.query(params, function(err, data) {
//     if (err) {
//         console.error("Unable to query. Error:", JSON.stringify(err, null, 2));
//     } else {
//         console.log("Query succeeded.");
//         data.Items.forEach(function(item) {
//             console.log(" -", item.time + ": " + item.data);
//         });
//     }
// });
docClient.scan(params, onScan);

function onScan(err, data) {
    if (err) {
        console.error("Unable to scan the table. Error JSON:", JSON.stringify(err, null, 2));
    } else {
        // print all the movies
        console.log("Scan succeeded.");
        data.Items.forEach(function(item) {
           console.log(
                item.time);
        });

        // continue scanning if we have more movies, because
        // scan can retrieve a maximum of 1MB of data
        if (typeof data.LastEvaluatedKey != "undefined") {
            console.log("Scanning for more...");
            params.ExclusiveStartKey = data.LastEvaluatedKey;
            docClient.scan(params, onScan);
        }
    }
}
