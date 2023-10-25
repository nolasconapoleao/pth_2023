require('dotenv').config();
const API_URL = process.env.API_URL;
const PUBLIC_KEY = process.env.PUBLIC_KEY;
const PRIVATE_KEY = process.env.PRIVATE_KEY;
const DEPLOYED_CONTRACT_ADDRESS = process.env.DEPLOYED_CONTRACT_ADDRESS;

const { createAlchemyWeb3 } = require("@alch/alchemy-web3");
const web3 = createAlchemyWeb3(API_URL);
const contract = require("../artifacts/contracts/VIPMembership.sol/VIPMembership.json");

const VIPContract = new web3.eth.Contract(contract.abi, DEPLOYED_CONTRACT_ADDRESS, {
    from: PUBLIC_KEY
});

async function remove_member(address) {
    const nonce = await web3.eth.getTransactionCount(PUBLIC_KEY, 'latest'); // get latest nonce
    const gasEstimate = await VIPContract.methods.removeMember(address).estimateGas(); // estimate gas

    // Create the transaction
    const tx = {
      'from': PUBLIC_KEY,
      'to': DEPLOYED_CONTRACT_ADDRESS,
      'nonce': nonce,
      'gas': gasEstimate, 
      'data': VIPContract.methods.removeMember(address).encodeABI()
    };

    // Sign the transaction
    const signPromise = web3.eth.accounts.signTransaction(tx, PRIVATE_KEY);
    signPromise.then((signedTx) => {
      web3.eth.sendSignedTransaction(signedTx.rawTransaction, function(err, hash) {
        if (!err) {
          console.log("The hash of your transaction is: ", hash, "\n Check Alchemy's Mempool to view the status of your transaction!");
        } else {
          console.log("Something went wrong when submitting your transaction:", err)
        }
      });
    }).catch((err) => {
      console.log("Promise failed:", err);
    });
}

async function main() {
  message = await VIPContract.methods.isAddressVIP("0x5FbDB2315678afecb367f032d93F642f64180aa3").call();
  console.log("This member is VIP?" + message);
  
  // await remove_member("0x5FbDB2315678afecb367f032d93F642f64180aa3");
}

main()
