#include <iostream>

#include "libsample/MathUtils.h"
#include "http_client.hpp"
#include "my_keys.hpp"
#include "InfInt.h"
#include <cmath>
#include "string_manipulation.hpp"

#include <json/single_include/nlohmann/json.hpp>

int main() {
  // Support purchase of membership with offchain payment

  /**
   * 1. Request call to oracle to retrieve the conversion rate for USD/ETH
   * GET https://min-api.cryptocompare.com/data/price?fsym=USD&tsyms=ETH
   */
  const std::string coin_rate_url = "https://min-api.cryptocompare.com/data/price?fsym=ETH&tsyms=USD";
  const std::string rate_response = get_request(coin_rate_url);

  nlohmann::json rate = nlohmann::json::parse(rate_response);
  InfInt ratio {rate["USD"].dump() };
  std::cout << "Eth to Dollar: " << ratio << std::endl;

  /** 
    * 2. Request api call to stripe payment invoice
    * curl https://api.stripe.com/v1/payment_intents/pi_3O4tGTDLtNgsHe8R0eYXmw1R \
    * -u STRIPE_API_KEY: \
    */
  const std::string stripe_payment_url = "https://api.stripe.com/v1/payment_intents/pi_3O5FtUDLtNgsHe8R0TWA252C";
  const std::string payment_response = get_request(stripe_payment_url, stripe_api_key);

  nlohmann::json payment = nlohmann::json::parse(payment_response);
  std::cout << "Payment: " << payment["amount"] << std::endl;
  InfInt payment_dollar { payment["amount"].dump() };

  /**
   * 3. Check if the payment amount matches the membership price
   * and payment details match the product intended
   * https://abi.hashex.org/
   */
  const std::string contract_address = "0x3e7ad68720f22F2EcE8d376d2CFE419524C5108D";
  const std::string price_url = "https://api-sepolia.etherscan.io/api?module=proxy&action=eth_call&to="+contract_address+"&data=0xb08d563c";
  const std::string price_response = get_request(price_url);

  nlohmann::json price = nlohmann::json::parse(price_response);
  std::string hexString = removeLeadingZerosAnd0x(price["result"]);
  uint32_t price_wei_uint = std::stoul(hexString, nullptr, 16);

  InfInt payment_wei = payment_dollar * ratio * InfInt{"1000000000000000000"};
  std::cout << "Payment in wei: " << payment_wei << std::endl;
  InfInt price_wei {price_wei_uint};

  if(price_wei < payment_wei) {
    std::cout << "Transaction succeeded" << std::endl;
  } else {
    std::cout << "Payment bellow price" << std::endl;
    return 1;
  }

  /**
   * 4. Publish payment confirmation to the blockchain
   * 
   */

  // Payment adds address to vip list

  return 0;
}
