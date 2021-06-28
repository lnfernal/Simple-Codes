
struct trade {
	int itemid;
	int count;
};
struct playertrade {
	vector<trade> trades;
};

/*playerinfo*/ 
playertrade tradee;
string tradingme = "";
int lasttradeid = 0;
bool accepted = false;
bool dotrade = false;
bool trading = false;
bool canceled = false;
string itemlist = "";

//event packets
if (cch.find("action|trade_accept\nstatus|") == 0) {
	std::stringstream ss(cch);
	std::string to;
	int status = -1;
	while (std::getline(ss, to, '\n')) {
		vector<string> ex = explode("|", to);
		if (ex[0] == "status") {
			if (has_only_digits(ex[1])) status = atoi(ex[1].c_str());
		}
	}
	if (status < 0 || status > 1) continue;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
				if (status == 1) {
					if (pdata(currentPeer)->accepted) {
						packet::onforcetradeend(peer);
						packet::onforcetradeend(currentPeer);
						bool pkey = false;
						string keytext = "";
						string keytext2 = "";
						for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
							if (pdata(peer)->tradee.trades[i].itemid == 1424) keytext = "\nadd_label|small|`4WARNING: `oYou are about to sell your world `#" + world->name + " `o- The world lock ownership will be transferred over to `w" + pdata(currentPeer)->displayName + "`o.|left|\nadd_spacer|small|", keytext2 = "\nadd_label|small|`4SCAM WARNING: `oYou are buying this world, `#" + world->name + "`o. Don't buy a world just to get its rare item because scammers can easily place secret doors allowing someone to jump in and `4steal the items back `oafter a trade!|left|\nadd_spacer|small|";
						}
						for (int i = 0; i < pdata(currentPeer)->tradee.trades.size(); i++) {
							if (pdata(currentPeer)->tradee.trades[i].itemid == 1424) keytext2 = "\nadd_label|small|`4WARNING: `oYou are about to sell your world `#" + world->name + " `o- The world lock ownership will be transferred over to `w" + pdata(peer)->displayName + "`o.|left|\nadd_spacer|small|", keytext = "\nadd_label|small|`4SCAM WARNING: `oYou are buying this world, `#" + world->name + "`o. Don't buy a world just to get its rare item because scammers can easily place secret doors allowing someone to jump in and `4steal the items back `oafter a trade!|left|\nadd_spacer|small|";
						}
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small|\n\nadd_label|small|`4You'll give:``|left|4|\nadd_spacer|small|" + TradeMessageDialog(peer, 0) + "\nadd_spacer|small|\nadd_label|small|`2You'll get:``|left|4|\nadd_spacer|small|" + TradeMessageDialog(currentPeer, 1) + "\nadd_spacer|small|" + keytext + "\nadd_button|dothetrade|`oDo The Trade!``|0|0|\nadd_button|notrade|`oCancel``|0|0|");
						Player::OnDialogRequest(currentPeer, "add_label_with_icon|big|`wTrade Confirmation``|left|1366|\nadd_spacer|small|\n\nadd_label|small|`4You'll give:``|left|4|\nadd_spacer|small|" + TradeMessageDialog(currentPeer, 0) + "\nadd_spacer|small|\n\nadd_label|small|`2You'll get:``|left|4|\nadd_spacer|small|" + TradeMessageDialog(peer, 1) + "\nadd_spacer|small|" + keytext2 + "\nadd_button|dothetrade|`oDo The Trade!``|0|0|\nadd_button|notrade|`oCancel``|0|0|");
					}
					else {
						packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|0\naccepted|1", true);
						pdata(peer)->accepted = true;
					}
				}
				if (status == 0) {
					packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|0\naccepted|0", true);
					pdata(peer)->accepted = false;
				}
			}
		}
	}
}
if (cch.find("action|trade_cancel") == 0) {
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
				reset_trade(currentPeer, true);
				Player::OnTextOverlay(currentPeer, pdata(peer)->displayName + " `wcancelled the trade.");
			}
		}
	}
	reset_trade(peer, true);
	Player::OnTextOverlay(peer, "`wYou cancelled the trade.");
}
if (cch.find("action|trade_started") == 0) {
	std::stringstream ss(cch);
	std::string to;
	int idx = -1;
	while (std::getline(ss, to, '\n')) {
		vector<string> infoDat = explode("|", to);
		if (infoDat.size() == 2) {
			if (infoDat[0] == "netid") {
				if (has_only_digits(infoDat[1])) {
					idx = atoi(infoDat[1].c_str());
				}
				else continue;
			}
			if (idx == -1 || idx > itemDefs.size() || idx < 0) continue;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					if (pdata(currentPeer)->netID == idx) {
						if (pdata(peer)->tradingme == "") {
							packet::ontradestatus(peer, pdata(currentPeer)->netID, "", pdata(currentPeer)->displayName, "locked|0\nreset_locks|1\naccepted|0", false);
						}
						else {
							packet::ontradestatus(peer, pdata(currentPeer)->netID, "", pdata(currentPeer)->displayName, pdata(currentPeer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
							packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
						}
					}
				}
			}
		}
	}
}
if (cch.find("action|mod_trade") == 0) {
	std::stringstream ss(cch);
	std::string to;
	int id = -1;
	while (std::getline(ss, to, '\n')) {
		vector<string> infoDat = explode("|", to);
		if (infoDat.size() == 2) {
			if (infoDat[0] == "itemID") {
				if (has_only_digits(infoDat[1])) {
					id = atoi(infoDat[1].c_str());
				}
			}
		}
		if (id == -1 || id > itemDefs.size() || id < 0) continue;
		if (id == 18 || id == 32 || getItemDef(id).properties & Property_Untradable && id != 1424) Player::OnTextOverlay(peer, "`wYou'd be sorry sorry if you lost that!");
		else {
			if (!have_in_inv(peer, id)) continue;
			pdata(peer)->lasttradeid = id;
			int count = stoi(GetItemCount(peer, id));
			if (count > 1) Player::OnDialogRequest(peer, "add_label_with_icon|big|`2Trade`w " + getItemDef(id).name + "``|left|" + std::to_string(id) + "|\nadd_textbox|`2Trade how many?|\nadd_text_input|itemcount||" + to_string(count) + "|3|\nend_dialog|tradedialog|Cancel|Ok|\n");
			else {
				int am = 0; int idx = -1;
				for (int i = 0; i < pdata(peer)->inventory.items.size(); i++) {
					if (pdata(peer)->inventory.items[i].itemID == pdata(peer)->lasttradeid) {
						am = pdata(peer)->inventory.items[i].itemCount;
					}
				}
				if (am < 1) {
					Player::OnConsoleMessage(peer, "You dont have that amount");
					break;
				}
				for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
					if (pdata(peer)->tradee.trades[i].itemid == pdata(peer)->lasttradeid) idx = i;
				}
				if (idx != -1) pdata(peer)->tradee.trades[idx].count = 1;
				else {
					trade trd;
					trd.itemid = pdata(peer)->lasttradeid;
					trd.count = 1;
					pdata(peer)->tradee.trades.push_back(trd);
				}
				string list1 = "";
				for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
					if (i == 0) {
						list1 += "add_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
					}
					else {
						list1 += "\nadd_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
					}
				}
				pdata(peer)->itemlist = list1;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
							if (pdata(currentPeer)->accepted) pdata(currentPeer)->accepted = false;
							packet::ontradestatus(peer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
							packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
							Player::PlayAudio(peer, "audio/tile_removed.wav", 0), Player::PlayAudio(currentPeer, "audio/tile_removed.wav", 0);
							Player::OnTextOverlay(peer, "The deal has changed!"), Player::OnTextOverlay(currentPeer, "The deal has changed!");
						}
						else packet::ontradestatus(peer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", false);
					}
				}
			}
		}
	}
}
if (cch.find("action|rem_trade") == 0) {
	std::stringstream ss(cch);
	std::string to;
	int id = -1;
	int idx = -1;
	while (std::getline(ss, to, '\n')) {
		vector<string> infoDat = explode("|", to);
		if (infoDat.size() == 2) {
			if (infoDat[0] == "itemID") {
				if (has_only_digits(infoDat[1])) {
					id = atoi(infoDat[1].c_str());
				}
			}
		}
		if (id == -1 || id > itemDefs.size() || id < 0) continue;
		for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
			if (pdata(peer)->tradee.trades[i].itemid == id) idx = i;
		}
		if (idx == -1) break;
		pdata(peer)->tradee.trades.erase(pdata(peer)->tradee.trades.begin() + idx);
		string list1 = "";
		for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
			if (i == 0) list1 += "add_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
			else list1 += "\nadd_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
		}
		pdata(peer)->itemlist = list1;
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
					packet::ontradestatus(peer, pdata(currentPeer)->netID, "", pdata(currentPeer)->displayName, pdata(currentPeer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
					packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
					Player::PlayAudio(peer, "audio/tile_removed.wav", 0), Player::PlayAudio(currentPeer, "audio/tile_removed.wav", 0);
					Player::OnTextOverlay(peer, "The deal has changed!"), Player::OnTextOverlay(currentPeer, "The deal has changed!");
				}
				else packet::ontradestatus(peer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", false);
			}
		}
	}
}

//buttons
if (btn == "trade") {
	pdata(peer)->trading = true;
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (pdata(peer)->lastwrench == pdata(currentPeer)->rawName) {
				if (pdata(currentPeer)->tradingme == pdata(peer)->rawName || pdata(currentPeer)->tradingme == "") {
					if (pdata(peer)->tradingme == "") {
						Player::OnConsoleMessage(peer, "You started trading with " + pdata(currentPeer)->rawName);
						Player::PlayAudio(currentPeer, "audio/cash_register.wav", 0);
						Player::OnConsoleMessage(currentPeer, "`#TRADE ALERT : `w" + pdata(peer)->rawName + " `owants to trade with you! To start, use the `wWrench `oon that person's wrench icon,or type `w/trade " + pdata(peer)->rawName);
					}
					packet::onstarttrade(peer, currentPeer);
					pdata(currentPeer)->tradingme = pdata(peer)->rawName;
				}
				else {
					Player::OnConsoleMessage(peer, "That player is trading someone else");
					reset_trade(peer, false);
				}
			}
		}
	}
}
if (btn == "dothetrade") {
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
				if (pdata(peer)->canceled) {
					reset_trade(peer, false);
					break;
				}
				if (pdata(currentPeer)->dotrade) {
					for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
						int val = 0;
						if (i == 0) val = 300; if (i == 1) val = 800; if (i == 2) val = 1300; if (i == 3) val = 1800;
						packet::sendtrade(peer, pdata(peer)->tradee.trades[i].itemid, pdata(peer)->netID, pdata(currentPeer)->netID, val);
						packet::sendtrade(currentPeer, pdata(peer)->tradee.trades[i].itemid, pdata(peer)->netID, pdata(currentPeer)->netID, val);
						if (pdata(peer)->tradee.trades[i].itemid != 1424) AddItemToInv(currentPeer, pdata(peer)->tradee.trades[i].itemid, pdata(peer)->tradee.trades[i].count);
						RemoveInventoryItem(peer, pdata(peer)->tradee.trades[i].itemid, pdata(peer)->tradee.trades[i].count, true);
						Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					}
					for (int i = 0; i < pdata(currentPeer)->tradee.trades.size(); i++) {
						int val = 0;
						if (i == 0) val = 300; if (i == 1) val = 800; if (i == 2) val = 1300; if (i == 3) val = 1800;
						packet::sendtrade(peer, pdata(currentPeer)->tradee.trades[i].itemid, pdata(currentPeer)->netID, pdata(peer)->netID, val);
						packet::sendtrade(currentPeer, pdata(currentPeer)->tradee.trades[i].itemid, pdata(currentPeer)->netID, pdata(peer)->netID, val);
						if (pdata(currentPeer)->tradee.trades[i].itemid != 1424) AddItemToInv(peer, pdata(currentPeer)->tradee.trades[i].itemid, pdata(currentPeer)->tradee.trades[i].count);
						RemoveInventoryItem(currentPeer, pdata(currentPeer)->tradee.trades[i].itemid, pdata(currentPeer)->tradee.trades[i].count, true);
						Player::PlayAudio(currentPeer, "audio/change_clothes.wav", 0);
					}
					Player::OnWorldMessage(peer, pdata(peer)->displayName + " `1traded " + TradeMessageConsole(peer) + " to " + pdata(currentPeer)->displayName);
					Player::OnWorldMessage(peer, pdata(currentPeer)->displayName + " `1traded " + TradeMessageConsole(currentPeer) + " to " + pdata(peer)->displayName);
					Player::PlayAudio(peer, "audio/keypad_hit.wav", 0), Player::PlayAudio(currentPeer, "audio/keypad_hit.wav", 0);
					for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
						if (pdata(peer)->tradee.trades[i].itemid == 1424) {
							world->owner = pdata(currentPeer)->rawName;
							world->ownerDisplayName = pdata(currentPeer)->displayName;
							ChangeName2(currentPeer);
							ChangeName2(peer);
							ENetPeer* currentPeerx;
							for (currentPeerx = server->peers;
								currentPeerx < &server->peers[server->peerCount]; ++currentPeerx) {
								if (currentPeerx->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeerx)) {
									packet::PlayAudio(currentPeerx, "audio/use_lock.wav");
									Player::OnTalkBubble(currentPeerx, pdata(currentPeer)->netID, " `5[```w" + world->name + "`` has been `$World Locked`` by " + world->ownerDisplayName + "`5]``", true);
								}
							}
							Player::OnWorldMessage(peer, "`5[`w" + world->name + " `ohas been `$World Locked `oby `o" + world->ownerDisplayName + "`5]``");
						}
					}
					for (int i = 0; i < pdata(currentPeer)->tradee.trades.size(); i++) {
						if (pdata(currentPeer)->tradee.trades[i].itemid == 1424) {
							world->owner = pdata(peer)->rawName;
							world->ownerDisplayName = pdata(peer)->displayName;
							ChangeName2(peer);
							ChangeName2(currentPeer);
							ENetPeer* currentPeerx;
							for (currentPeerx = server->peers;
								currentPeerx < &server->peers[server->peerCount]; ++currentPeerx) {
								if (currentPeerx->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeerx)) {
									packet::PlayAudio(currentPeerx, "audio/use_lock.wav");
									Player::OnTalkBubble(currentPeerx, pdata(peer)->netID, " `5[```w" + world->name + "`` has been `$World Locked`` by " + world->ownerDisplayName + "`5]``", true);
								}
							}
							Player::OnWorldMessage(peer, "`5[`w" + world->name + " `ohas been `$World Locked `oby `o" + world->ownerDisplayName + "`5]``");
						}
					}
					reset_trade(peer, true); reset_trade(currentPeer, true);
				}
				else {
					pdata(peer)->dotrade = true;
					Player::OnTalkBubble(peer, pdata(peer)->netID, "`o[`wTrade accepted, waiting for other player to accept`o]", true);
					Player::OnTalkBubble(currentPeer, pdata(peer)->netID, "`o[`wTrade accepted, waiting for you to accept`o]", true);
				}
			}
		}
	}
}
if (btn == "notrade") {
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
				pdata(currentPeer)->canceled = true;
				reset_trade(currentPeer, false);
				Player::OnTextOverlay(currentPeer, "The player canceled the trade");
			}
		}
	}
	reset_trade(peer, false);
}

//action|dialog
bool istradedialog = false;
int itemcount = 0;
if (infoDat[0] == "dialog_name" && infoDat[1] == "tradedialog") istradedialog = true;
if (istradedialog) if (infoDat[0] == "itemcount") itemcount = atoi(infoDat[1].c_str());
if (istradedialog) {
	if (has_only_digits(to_string(itemcount))) {
		if (itemcount < 0 || itemcount > 200) Player::OnConsoleMessage(peer, "You cant trade more than 200 or less than 0");
		else {
			int am = 0; int idx = -1;
			for (int i = 0; i < pdata(peer)->inventory.items.size(); i++) {
				if (pdata(peer)->inventory.items[i].itemID == pdata(peer)->lasttradeid) {
					am = pdata(peer)->inventory.items[i].itemCount;
				}
			}
			if (am < itemcount) {
				Player::OnConsoleMessage(peer, "You dont have that amount");
				break;
			}
			if (itemcount < 1) itemcount = 1;
			for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
				if (pdata(peer)->tradee.trades[i].itemid == pdata(peer)->lasttradeid) idx = i;
			}
			if (idx != -1) pdata(peer)->tradee.trades[idx].count = itemcount;
			else {
				trade trd;
				trd.itemid = pdata(peer)->lasttradeid;
				trd.count = itemcount;
				pdata(peer)->tradee.trades.push_back(trd);
			}
			string list1 = "";
			for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
				if (i == 0) {
					list1 += "add_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
				}
				else {
					list1 += "\nadd_slot|" + std::to_string(pdata(peer)->tradee.trades[i].itemid) + "|" + std::to_string(pdata(peer)->tradee.trades[i].count);
				}
			}
			pdata(peer)->itemlist = list1;
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					if (pdata(currentPeer)->rawName == pdata(peer)->tradingme) {
						if (pdata(currentPeer)->accepted) pdata(currentPeer)->accepted = false;
						packet::ontradestatus(peer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
						packet::ontradestatus(currentPeer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", true);
						Player::PlayAudio(peer, "audio/tile_removed.wav", 0), Player::PlayAudio(currentPeer, "audio/tile_removed.wav", 0);
						Player::OnTextOverlay(peer, "The deal has changed!"), Player::OnTextOverlay(currentPeer, "The deal has changed!");
					}
					else packet::ontradestatus(peer, pdata(peer)->netID, "", pdata(peer)->displayName, pdata(peer)->itemlist + "locked|0\nreset_locks|1\naccepted|0", false);
				}
			}
		}
	}
}

//voids
void reset_trade(ENetPeer* peer, bool end) {
	if (end) {
		packet::onforcetradeend(peer);
	}
	pdata(peer)->accepted = false;
	pdata(peer)->tradee.trades.clear();
	pdata(peer)->tradingme = "";
	pdata(peer)->itemlist = "";
	pdata(peer)->lasttradeid = 0;
	pdata(peer)->dotrade = false;
	pdata(peer)->trading = false;
	pdata(peer)->canceled = false; 
}

//string
string TradeMessageDialog(ENetPeer* peer, bool getting) {
	if (pdata(peer)->tradee.trades.size() < 1) {
		string a = "\nadd_textbox|";
		a += (getting ? "`4" : "`2");
		a += "Nothing!|left|";
		return a;
	}
	string fmt;
	for (auto& t : pdata(peer)->tradee.trades) {
		fmt += "\nadd_label_with_icon|small|`o(`w" + to_string(t.count) + "`o) `w" + getItemDef(t.itemid).name + "``|left|" + to_string(t.itemid) + "|";
	}
	return fmt;
}
string TradeMessageConsole(ENetPeer* peer) {
	string fmt;
	for (int i = 0; i < pdata(peer)->tradee.trades.size(); i++) {
		if (i > 0) fmt += ", " + std::to_string(pdata(peer)->tradee.trades[i].count) + " " + getItemDef(pdata(peer)->tradee.trades[i].itemid).name;
		else fmt += std::to_string(pdata(peer)->tradee.trades[i].count) + " " + getItemDef(pdata(peer)->tradee.trades[i].itemid).name;
	}
	if (fmt == "") fmt = "Nothing";
	return fmt;
}
