#include "server.h"
#include "client.h"
#include <memory>
#include <string>
class Client;
Server::Server() {}
std::shared_ptr<Client> Server::add_client(std::string id) {
  for (auto &client : clients)
    if (client.first->get_id() == id) {
      int r = std::rand() % 9000 + 1000;
      id += r;
    }
  std::shared_ptr<Client> newclient = std::make_shared<Client>(id, *this);
  clients.insert({newclient, 5});
  return newclient;
}
std::shared_ptr<Client> Server::get_client(std::string id) const {
  for (auto &client : clients)
    if (client.first->get_id() == id)
      return client.first;
  return nullptr;
}
double Server::get_wallet(std::string id) const {
  for (auto &client : clients)
    if (client.first->get_id() == id)
      return client.second;
  return -1;
}
std::vector<std::string> split(std::string s, std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) {
    std::string delimiter = "-";
    auto tokens = split(trx, delimiter);
    if(tokens.size() < 3) {
      throw std::runtime_error("the trx is not in stand format");
      return false;
    }
    sender = tokens[0]; receiver = tokens[1]; value = std::stod(tokens[2]);
    return true;
                       }
bool Server::add_pending_trx(std::string trx, std::string signature) const {
  std::string sender , receiver;
  double value;
  parse_trx(trx, sender, receiver, value);
  if(!get_client(sender) || !get_client(receiver)) return false;
  if(get_wallet(sender) < value) return false;
  bool authentic = crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature);
  if(authentic) {
    pending_trxs.push_back(trx);
    return true;
  }else return false;

}
size_t Server::mine(){
  std::string mempool;
  for(auto pending_trx : pending_trxs) {
    mempool += pending_trx;
  }
  size_t nonce = 0;
  while(true) {
    for(auto &client : clients) {
      nonce = client.first->generate_nonce();
      std::string hash{crypto::sha256(mempool + std::to_string(nonce))};
      if(hash.substr(0, 10).find("000") != std::string::npos) {
        client.second += 6.25;
        for(auto pending_trx : pending_trxs) {
          std::string sender, receiver;
          double value;
          parse_trx(pending_trx, sender, receiver, value);
          for(auto &client: clients) {
            if(client.first->get_id() == sender) {
              client.second -= value;
            } else if(client.first->get_id() == receiver) {
              client.second += value;
            }
          }
        }
        pending_trxs.clear();
        std::cout << "miner " << client.first->get_id() << " successfully get the award!" << std::endl;
        return nonce;
      }
    }
  }
}
