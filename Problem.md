
Sections
1. Request call to obtain conversion rate for ETH/USD
```json
GET https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD`

Output format:
{"ETH":0.0005594}
```

2. Request api call to stripe payment invoice
Register to stripe
https://dashboard.stripe.com/register

```json
curl https://api.stripe.com/v1/payment_intents/pi_3O4tGTDLtNgsHe8R0eYXmw1R -u STRIPE_API_KEY:

{
  "id": "pi_3O4tGTDLtNgsHe8R0eYXmw1R",
  "amount": 2000,
  "customer": "0x1234567890123456789012345678901234567890",
  ...
}
```

3. Check if the payment amount matches the membership price
and payment details match the product intended
```json
Contract address: 0x3e7ad68720f22F2EcE8d376d2CFE419524C5108D
Blockexplorer: https://sepolia.etherscan.io/
API docs: https://docs.etherscan.io/api-endpoints/geth-parity-proxy#eth_call
ABI utility tool: https://abi.hashex.org/

GET https://api-sepolia.etherscan.io/api?module=proxy&action=eth_call&to=0x3e7ad68720f22F2EcE8d376d2CFE419524C5108D&data=0xb08d563c
```

4. Publish payment confirmation to the blockchain
``` 
Request goes through node ngrok server
```
