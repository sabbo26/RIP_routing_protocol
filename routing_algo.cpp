#include "node.h"
#include <iostream>

using namespace std;

void routingAlgo(vector<RoutingNode*> nd) {
	//Your code here
	for (int j = 0; j < nd.size(); j++) {
		for (int i = 0; i < nd.size(); i++) {
			nd[i]->sendMsg();
		}
	}

}


void RoutingNode::recvMsg(RouteMsg* msg) {
	//your code here
	string sender_ip = msg->from;
	string receiving_interface = msg->recvip;
	routingtbl* received_routing_table = msg->mytbl;

	for (int i = 0; i < received_routing_table->tbl.size(); i++) {

		bool new_val = true;

		RoutingEntry received_routing_entry = received_routing_table->tbl[i];

		for (int j = 0; j < mytbl.tbl.size(); j++) {

			if (mytbl.tbl[j].dstip == received_routing_entry.dstip) {

				if (mytbl.tbl[j].cost > received_routing_entry.cost + 1) {
					mytbl.tbl[j].cost = received_routing_entry.cost + 1 ;
					mytbl.tbl[j].ip_interface = receiving_interface;
					mytbl.tbl[j].nexthop = sender_ip;
				}
				new_val = false;
				break;
			}

		}

		// in case routing entry is inserted for first time

		if (new_val) {
			RoutingEntry new_entry;

			new_entry.cost = received_routing_entry.cost + 1;
			new_entry.ip_interface = receiving_interface;
			new_entry.dstip = received_routing_entry.dstip;
			new_entry.nexthop = sender_ip;

			mytbl.tbl.push_back(new_entry);
		}
	}


}




