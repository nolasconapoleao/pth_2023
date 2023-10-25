#include <iostream>

#include "libsample/MathUtils.h"

int main() {
  // Support purchase of nft with offchain payment

  /**
   * 1. Request call to oracle to retrieve the conversion rate for ETH/USD
   * https://abi.hashex.org/
   * GET https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD
   * GET https://api.etherscan.io/api?module=stats&action=ethprice&apikey=YourApiKeyToken
   */

  /** 
    * 2. Request api call to stripe payment invoice
    * curl https://api.stripe.com/v1/payment_intents/pi_3O4tGTDLtNgsHe8R0eYXmw1R \
    * -u sk_test_51O4swkDLtNgsHe8RKBrWLLvxvXfgZ88hpKoPWNzzrt8gfX56WZD5db4uowRxZDw7brmbc0d6Pv45SUqiORTJI43z00qxSc5iee:
    */
 
  /**
   * 3. Check if the payment amount matches the nft price 
   * and payment details match the product intended
   */

  /**
   * 4. Publish payment confirmation to the blockchain
   * 
   */
  

  // Payment triggers minting of nft

  return 0;
}
