//struct playerinfo
int billboardid = 0;
	int billboardtab = 0;
	int billboardprice = 0;
	int billboardperwhat = 0;
	
void SendBillBoard(ENetPeer* peer) {
	string fota = "";
	if (pdata(peer)->billboardid != 0) {
		fota = "\nadd_label|small|`2Billboard Item : `w" + getItemDef(pdata(peer)->billboardid).name + "|left|";
	}
	if (pdata(peer)->billboardperwhat == 0) {
		Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|`wTrade Billboard|left|8282|\nadd_spacer|small|" + fota + "\nadd_item_picker|billitem|`wSelect Billboard Item|Choose an item to put on your billboard|\nadd_checkbox|showbill|Show billboard|" + to_string(pdata(peer)->billboardtab) + "|\nadd_text_input|billprice|Price of item:|" + to_string(pdata(peer)->billboardprice) + "|5|\nadd_checkbox|wlperitem|World Lock per item|0|\nadd_checkbox|itemperwl|Item per world lock|1|\nadd_quick_exit|\nend_dialog|updatebillboard|Cancel|Update|");
	}
	else {
		Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|`wTrade Billboard|left|8282|\nadd_spacer|small|" + fota + "\nadd_item_picker|billitem|`wSelect Billboard Item|Choose an item to put on your billboard|\nadd_checkbox|showbill|Show billboard|" + to_string(pdata(peer)->billboardtab) + "|\nadd_text_input|billprice|Price of item:|" + to_string(pdata(peer)->billboardprice) + "|5|\nadd_checkbox|wlperitem|World Lock per item|1|\nadd_checkbox|itemperwl|Item per world lock|0|\nadd_quick_exit|\nend_dialog|updatebillboard|Cancel|Update|");
	}
}
void BillBoard(ENetPeer* peer, int id, int price, int enabled, int perwhat) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			GamePacket p1 = packetEnd(appendInt(appendInt(appendInt(appendInt(appendIntx(appendString(createPacket(), "OnBillboardChange"), pdata(peer)->netID), id), enabled), price), perwhat));
			memcpy(p1.data + 8, &(pdata(peer)->netID), 4);
			ENetPacket* packet1 = enet_packet_create(p1.data, p1.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet1);
			delete p1.data;
		}
	}
}

//action|dialog
string showbillboard = "";
						string billboardprice = "";
						bool isBillBoard = false;
						string wlperitem = "";
						string itemperwl = "";
						int billitem = 0;
						bool billpicker = false;
if (infoDat[0] == "billitem") billpicker = true;
if (infoDat[0] == "dialog_name" && infoDat[1] == "updatebillboard") isBillBoard = true;

if (billpicker) if (infoDat[0] == "billitem") billitem = atoi(infoDat[1].c_str()); 
								if (billpicker) {
									if (world == nullptr) continue;
									if (pdata(peer)->currentWorld == "EXIT") continue;
									if (world == nullptr || world->name == "EXIT" || serverIsFrozen) break;
									if (getItemDef(billitem).properties & Property_Untradable) {
										SendBillBoard(peer);
										Player::OnTextOverlay(peer, "You can't put untradeables!");
										continue;
									}
									if (getItemDef(billitem).blockType == BlockTypes::LOCK) {
										SendBillBoard(peer);
										Player::OnTextOverlay(peer, "You can't put locks!");
										continue;
									}
									pdata(peer)->billboardid = billitem;
									BillBoard(peer, pdata(peer)->billboardid, pdata(peer)->billboardprice, pdata(peer)->billboardtab, pdata(peer)->billboardperwhat);
									SendBillBoard(peer);
									player::SaveData(peer);
								}
								if (isBillBoard) {
									if (infoDat[0] == "itemperwl") itemperwl = infoDat[1];
									if (infoDat[0] == "showbill") showbillboard = infoDat[1];
									if (infoDat[0] == "wlperitem") wlperitem = infoDat[1];
									if (infoDat[0] == "billprice") billboardprice = infoDat[1];
								}
								if (isBillBoard) {
									if (world == nullptr) continue;
									if (pdata(peer)->currentWorld == "EXIT") continue;
									if (world == nullptr || world->name == "EXIT" || serverIsFrozen) break;
									if (itemperwl == "") continue;
									if (wlperitem == "") continue;
									if (showbillboard == "") continue;
									if (billboardprice == "") continue;
									bool contains_non_int2 = !std::regex_match(billboardprice, std::regex("^[0-9]+$"));
									if (contains_non_int2 == true) {
										SendBillBoard(peer);
										Player::OnTextOverlay(peer, "Put numbers in price, not symbols...");
										continue;
									}
									if (wlperitem == "1" && itemperwl == "1") {
										SendBillBoard(peer);
										Player::OnTextOverlay(peer, "You can't have it both ways.");
										continue;
									}
									if (wlperitem == "0" && itemperwl == "0") {
										SendBillBoard(peer);
										Player::OnTextOverlay(peer, "You have to pick atleast one.");
										continue;
									}
									if (itemperwl == "1") {
										pdata(peer)->billboardperwhat = 0;
									}
									if (wlperitem == "1") {
										pdata(peer)->billboardperwhat = 1;
									}
									if (showbillboard == "0") {
										pdata(peer)->billboardtab = 0;
									}
									else if (showbillboard == "1") {
										pdata(peer)->billboardtab = 1;
									}
									pdata(peer)->billboardprice = stoi(billboardprice);
									BillBoard(peer, pdata(peer)->billboardid, pdata(peer)->billboardprice, pdata(peer)->billboardtab, pdata(peer)->billboardperwhat);
									SendBillBoard(peer); 
								}

//button
if (btn == "billboard") {
									SendBillBoard(peer);
								}
						
