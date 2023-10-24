#include <iostream>

#include "libsample/MathUtils.h"
#include "http_client.hpp"
#include "InfInt.h"
#include <cmath>

#include <json/single_include/nlohmann/json.hpp>

int main() {
  // Support purchase of membership with offchain payment

  /**
   * 1. Request call to oracle to retrieve the conversion rate for USD/ETH
   * GET https://min-api.cryptocompare.com/data/price?fsym=USD&tsyms=ETH
   */

  /** 
    * 2. Request api call to stripe payment invoice
    * curl https://api.stripe.com/v1/payment_intents/pi_3O4tGTDLtNgsHe8R0eYXmw1R \
    * -u STRIPE_API_KEY: \
    */

  /**
   * 3. Check if the payment amount matches the membership price
   * and payment details match the product intended
   * https://abi.hashex.org/
   */

  /**
   * 4. Publish payment confirmation to the blockchain
   * 
   */

  // Payment adds address to vip list

  return 0;
}
