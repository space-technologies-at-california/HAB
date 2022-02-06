import json
import base64
import boto3
from botocore.exceptions import ClientError
from urllib.parse import parse_qs

# Get table
dynamodb = boto3.resource('dynamodb')
table = dynamodb.Table('hab')

def lambda_handler(event, context):
    
    # Fetching and decoding data 
    req_body = event['body']
    if event['isBase64Encoded']:
        req_body = base64.b64decode(req_body).decode('utf-8')
    req_body = parse_qs(req_body)
   
    # Placing data into databse (includes error handling)
    
    try:
        response = table.put_item(
            Item={
                'time': req_body['transmit_time'][0],
                'data': req_body['data'][0]
            }
        )
    except ClientError as e:
        # For logging purposes
        print(e.response['Error']['Message'])
        
        # Trigger resend after some backoff period 
        return {'statusCode': 400} # 
    
    
    return {'statusCode': 200, 'body': "body: {}".format(req_body)}