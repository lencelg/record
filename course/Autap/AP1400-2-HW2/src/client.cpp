#include "../include/client.h"
#include <cstdlib>
#include <string>
Client::Client(std::string id, const Server &server) : id(id), server(&server) {
  crypto::generate_key(public_key, private_key);
}
std::string Client::get_id() { return id; }
std::string Client::get_publickey() const { return public_key; }
double Client::get_wallet() const { return server->get_wallet(id); }
std::string Client::sign(std::string txt) const {
  return crypto::signMessage(private_key, txt);
}
bool Client::transfer_money(std::string receiver, double value) {
  if (get_wallet() < value)
    return false;
  if (server->get_client(receiver) == nullptr)
    return false;
  std::string transaction_string =
      this->id + "-" + receiver + "-" + std::to_string(value);
  server->add_pending_trx(transaction_string, crypto::signMessage(private_key, transaction_string));
  return true;
}
size_t Client::generate_nonce() { return std::rand(); }
