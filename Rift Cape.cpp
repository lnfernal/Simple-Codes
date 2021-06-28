//dont forget add |" + editriftcape + "| to selfwrench
//tomakeitsavewhenentering, put this thing includes with UpdateALlClothes
PlayerRiftCape(peer, pdata(peer)->rifteffect, createRGBA(pdata(peer)->capeB, pdata(peer)->capeG, pdata(peer)->capeR, 255), createRGBA(pdata(peer)->capeB, pdata(peer)->capeG, pdata(peer)->capeR, 255), createRGBA(pdata(peer)->capeB, pdata(peer)->capeG, pdata(peer)->capeR, 255), createRGBA(pdata(peer)->capeB, pdata(peer)->capeG, pdata(peer)->capeR, 255), pdata(peer)->timedilation, pdata(peer)->collarcape);



string editriftcape = "";
if (pdata(peer)->cloth_back == 10424) {
       editriftcape = "\nadd_button|editriftcape|`$Rift Cape``|";
}



//voids/ints
struct TAlphaColorRec {
	char R = 'R';
	char G = 'G';
	char B = 'B';
	char A = 'A';
	char Color;
};
int createRGBA(int B, int G, int R, int A) {
	TAlphaColorRec zzacr;
	zzacr.R = R;
	zzacr.G = G;
	zzacr.B = B;
	zzacr.A = A;
	return zzacr.Color;
}
void PlayerRiftCape(ENetPeer* peer, int colum1, int colum2, int colum3, int colum4, int colum5, int colum6, int berapapacket)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			if (berapapacket == 5) //no time dilation
			{
				GamePacket p3s2 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2/*Cape Color*/), colum3), colum4/*kerah leher*/), colum5));
				memcpy(p3s2.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet2s2 = enet_packet_create(p3s2.data, p3s2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2s2);
				delete p3s2.data;

				GamePacket p33 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2/*Cape Color*/), colum3), colum4/*kerah leher*/), colum5));
				memcpy(p33.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet23 = enet_packet_create(p33.data, p33.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet23);
				delete p33.data;
			}
			else if (berapapacket == 2) {
				GamePacket p3ss = packetEnd(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2));
				memcpy(p3ss.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet2ss = enet_packet_create(p3ss.data, p3ss.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2ss);
				delete p3ss.data;

				GamePacket p3 = packetEnd(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2));
				memcpy(p3.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet2 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p3.data;
			}
			else if (berapapacket == 6) {
				GamePacket p3 = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2/*Cape Color*/), colum3), colum4/*kerah leher*/), colum5), colum6));
				auto respawnTimeout2 = colum6 + 00;
				auto deathFlag2 = 0x19;
				memcpy(p3.data + 24, &respawnTimeout2, 4);
				memcpy(p3.data + 56, &deathFlag2, 4);
				memcpy(p3.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet2 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p3.data;
				GamePacket p3s = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnRiftCape"), colum1), colum2/*Cape Color*/), colum3), colum4/*kerah leher*/), colum5), colum6));
				auto respawnTimeout = colum6 + 00;
				auto deathFlag = 0x19;
				memcpy(p3s.data + 24, &respawnTimeout, 4);
				memcpy(p3s.data + 56, &deathFlag, 4);
				memcpy(p3s.data + 8, &(pdata(peer)->netID), 4);
				ENetPacket* packet2s = enet_packet_create(p3s.data, p3s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2s);
				delete p3s.data;
			}
		}
	}
}

//putinplayerinfo
int capeR = 255;
int capeG = 255;
int capeB = 255;
int collarR = 255;
int collarB = 255;
int collarG = 255;
int timedilation = 30;
int rifteffect = 5091;
int collarcape = 2;
int checkbox_timedilation = 1;
int checkbox_capecollar = 1;
int checkbox_closedcape = 0;
int checkbox_opencapemovement = 0;
int checkbox_auraonoff = 1;
int checkbox_portalaura = 0;
int checkbox_starfieldaura = 0;
int checkbox_electricalaura = 1;
int collarR2 = 0;
int collarG2 = 0;
int collarB2 = 0;
int capeR2 = 0;
int capeG2 = 0;
int capeB2 = 0;
int udahsettingorno = false;

//action|dialog
string checkbox_starfieldaura = "";
string checkbox_portalaura = "";
string checkbox_auraonoff = "";
string checkbox_electricalaura = "";
bool riftcape = false;

if (infoDat[0] == "dialog_name" && infoDat[1] == "riftcape") { riftcape = true; }

								if (riftcape) {
									if (world == nullptr) continue;
									if (world->items == nullptr) continue;
									if (!world) continue;
									if (infoDat[0] == "checkbox_capecollar") {
										if (infoDat[1] == "1") {
											static_cast<PlayerInfo*>(peer->data)->checkbox_capecollar = 1;
										}
										else
										{
											static_cast<PlayerInfo*>(peer->data)->checkbox_capecollar = 0;
										}
									}
									if (infoDat[0] == "checkbox_timedilation") {
										if (infoDat[1] == "1") {
											static_cast<PlayerInfo*>(peer->data)->checkbox_timedilation = 1;
										}
										else {
											static_cast<PlayerInfo*>(peer->data)->checkbox_timedilation = 0;
										}
									}
									if (infoDat[0] == "checkbox_auraonoff") {
										checkbox_auraonoff = infoDat[1];
									}
									if (infoDat[0] == "checkbox_portalaura") {
										checkbox_portalaura = infoDat[1];
									}
									if (infoDat[0] == "checkbox_starfieldaura") {
										checkbox_starfieldaura = infoDat[1];
									}
									if (infoDat[0] == "checkbox_electricalaura") {
										if (checkbox_auraonoff == "1") {
											if (checkbox_portalaura == "1" && checkbox_starfieldaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_portalaura == "1" && checkbox_starfieldaura == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_portalaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_starfieldaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (infoDat[1] == "1") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_electricalaura = 1;
											}
											if (checkbox_starfieldaura == "1") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_starfieldaura = 1;
											}
											if (checkbox_portalaura == "1") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_portalaura = 1;
											}
											if (infoDat[1] == "0") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_electricalaura = 0;
											}
											if (checkbox_starfieldaura == "0") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_starfieldaura = 0;
											}
											if (checkbox_portalaura == "0") {
												static_cast<PlayerInfo*>(peer->data)->checkbox_portalaura = 0;
											}
										}
										else {
											if (checkbox_portalaura == "1" && checkbox_starfieldaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_portalaura == "1" && checkbox_starfieldaura == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_portalaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (checkbox_starfieldaura == "1" && infoDat[1] == "1") {
												Player::OnConsoleMessage(peer, "You can't have it both ways.");
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't have it both ways.", 0, true);
												break;
											}
											if (infoDat[1] == "1") {
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTurn off first the aura", 0, true);												break;
											}
											if (checkbox_starfieldaura == "1") {
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTurn off first the aura", 0, true);												break;
											}
											if (checkbox_portalaura == "1") {
												Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTurn off first the aura", 0, true);												break;
											}
										}
									}
									if (infoDat[0] == "timedilation") {
										string settimedilation = infoDat[1];
										if (settimedilation.size() > 2 || settimedilation.size() <= 0 || settimedilation.size() < 1)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set Time Dilation > 30", 0, true);
											break;
										}
										if (settimedilation.find_first_not_of("0123456789") != string::npos)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set Time Dilation with non digits", 0, true);											break;
										}
										if (stoi(settimedilation) < 0)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set Time Dilation <", 0, true);
											break;
										}
										if (settimedilation == "")
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set Time Dilation < 0", 0, true);
											break;
										}
										static_cast<PlayerInfo*>(peer->data)->timedilation = stoi(infoDat[1]);
									}
									if (infoDat[0] == "collarrgb") {
										string setcollarrgb = infoDat[1];
										if (setcollarrgb.size() > 11 || setcollarrgb.size() <= 0 || setcollarrgb.size() < 5)
										{
										Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (setcollarrgb.find_first_not_of("0123456789,") != string::npos)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB non digits", 0, true);											break;
										}
										vector<string> gay = explode(",", infoDat[1]); // more good & faster
										int R2 = atoi(gay[0].c_str());
										int G2 = atoi(gay[1].c_str());
										int B2 = atoi(gay[2].c_str()); //helped by kipas and samuel
										int A2 = 255;
										static_cast<PlayerInfo*>(peer->data)->collarR = static_cast<PlayerInfo*>(peer->data)->capeR;
										static_cast<PlayerInfo*>(peer->data)->collarG = static_cast<PlayerInfo*>(peer->data)->capeG;
										static_cast<PlayerInfo*>(peer->data)->collarB = static_cast<PlayerInfo*>(peer->data)->capeB;
										if (R2 < 0 || G2 < 0 || B2 < 0) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);											break;
										}
										if (R2 > 255 || G2 > 255 || B2 > 255) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);											break;
										}
									}
									if (infoDat[0] == "collarrgb2") {
										string setcollarrgb = infoDat[1];
										if (setcollarrgb.size() > 11 || setcollarrgb.size() <= 0 || setcollarrgb.size() < 5) {
											                                            Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (setcollarrgb.find_first_not_of("0123456789,") != string::npos)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB non digits", 0, true);
											break;
										}
										vector<string> gay = explode(",", infoDat[1]); // more good & faster
										int R2 = atoi(gay[0].c_str());
										int G2 = atoi(gay[1].c_str());
										int B2 = atoi(gay[2].c_str()); //helped by kipas and samuel
										int A2 = 255;
										static_cast<PlayerInfo*>(peer->data)->collarR2 = atoi(gay[0].c_str());
										static_cast<PlayerInfo*>(peer->data)->collarG2 = atoi(gay[1].c_str());
										static_cast<PlayerInfo*>(peer->data)->collarB2 = atoi(gay[2].c_str());
										if (R2 < 0 || G2 < 0 || B2 < 0) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (R2 > 255 || G2 > 255 || B2 > 255) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
									}
									if (infoDat[0] == "capergb2") {
										string setcapergb = infoDat[1];
										if (setcapergb.size() > 11 || setcapergb.size() <= 0 || setcapergb.size() < 5)
										{
											                                            Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (setcapergb.find_first_not_of("0123456789,") != string::npos)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB non digits", 0, true);
											break;
										}
										vector<string> gay = explode(",", infoDat[1]); // more good & faster
										int R = atoi(gay[0].c_str());
										int G = atoi(gay[1].c_str());
										int B = atoi(gay[2].c_str()); //helped by kipas and samuel
										int A = 255;
										static_cast<PlayerInfo*>(peer->data)->capeR2 = atoi(gay[0].c_str());
										static_cast<PlayerInfo*>(peer->data)->capeG2 = atoi(gay[1].c_str());
										static_cast<PlayerInfo*>(peer->data)->capeB2 = atoi(gay[2].c_str());
										//cout << R << endl;	

										if (R < 0 || G < 0 || B < 0) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (R > 255 || G > 255 || B > 255) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
									}
									if (infoDat[0] == "capergb") {
										string setcapergb = infoDat[1];
										if (setcapergb.size() > 11 || setcapergb.size() <= 0 || setcapergb.size() < 5)
										{
											                                            Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (setcapergb.find_first_not_of("0123456789,") != string::npos)
										{
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB non digits", 0, true);
											break;
										}
										vector<string> gay = explode(",", infoDat[1]); // more good & faster
										int R = atoi(gay[0].c_str());
										int G = atoi(gay[1].c_str());
										int B = atoi(gay[2].c_str()); //helped by kipas and samuel
										int A = 255;
										static_cast<PlayerInfo*>(peer->data)->capeR = atoi(gay[0].c_str());
										static_cast<PlayerInfo*>(peer->data)->capeG = atoi(gay[1].c_str());
										static_cast<PlayerInfo*>(peer->data)->capeB = atoi(gay[2].c_str());
										if (R < 0 || G < 0 || B < 0) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
										if (R > 255 || G > 255 || B > 255) {
											Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou can't set RGB > from 255", 0, true);
											break;
										}
									}
									int effect = static_cast<PlayerInfo*>(peer->data)->rifteffect;
									int collar = static_cast<PlayerInfo*>(peer->data)->collarcape;
									int timedilation2 = static_cast<PlayerInfo*>(peer->data)->timedilation;
									int A = 255;
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_capecollar == 1)
									{
										collar = 6;
									}
									if (checkbox_portalaura == "1")
									{
										effect = 2555;
									}
									if (checkbox_electricalaura == "1")
									{
										effect = 5091;
									}
									if (checkbox_starfieldaura == "1")
									{
										effect = 5091;
									}
									if (!static_cast<PlayerInfo*>(peer->data)->checkbox_timedilation == 1)
									{
										timedilation2 = 1000000000000000;
									}
									static_cast<PlayerInfo*>(peer->data)->rifteffect = effect;
									static_cast<PlayerInfo*>(peer->data)->collarcape = collar;
									static_cast<PlayerInfo*>(peer->data)->timedilation = timedilation2;
									PlayerRiftCape(peer, static_cast<PlayerInfo*>(peer->data)->rifteffect, createRGBA(static_cast<PlayerInfo*>(peer->data)->capeB, static_cast<PlayerInfo*>(peer->data)->capeG, static_cast<PlayerInfo*>(peer->data)->capeR, A), createRGBA(static_cast<PlayerInfo*>(peer->data)->capeB, static_cast<PlayerInfo*>(peer->data)->capeG, static_cast<PlayerInfo*>(peer->data)->capeR, A), createRGBA(static_cast<PlayerInfo*>(peer->data)->capeB, static_cast<PlayerInfo*>(peer->data)->capeG, static_cast<PlayerInfo*>(peer->data)->capeR, A), createRGBA(static_cast<PlayerInfo*>(peer->data)->capeB, static_cast<PlayerInfo*>(peer->data)->capeG, static_cast<PlayerInfo*>(peer->data)->capeR, A), static_cast<PlayerInfo*>(peer->data)->timedilation, static_cast<PlayerInfo*>(peer->data)->collarcape); //yg collar urutan 4 sama 5
								}
								if (btn == "instructions") {
									Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`oInstruction``|left|10424|\nadd_spacer|small|\nadd_textbox|`oUse RGB for setting a color (RED, GREEN, BLUE), portal aura for effect like portal, electrical aura for effect like electric.|0|0|\nadd_quick_exit|\n\nend_dialog|gazette|`oClose||");
								}
								if (btn == "editriftcape") {
									string starfield = "0";
									string portal = "0";
									string electrical = "0";
									string auraonoff = "0";
									string capecollar = "0";
									string R = to_string(static_cast<PlayerInfo*>(peer->data)->capeR) + ",";
									string G = to_string(static_cast<PlayerInfo*>(peer->data)->capeG) + ",";
									string B = to_string(static_cast<PlayerInfo*>(peer->data)->capeB);
									string collarR = to_string(static_cast<PlayerInfo*>(peer->data)->collarR) + ",";
									string collarG = to_string(static_cast<PlayerInfo*>(peer->data)->collarG) + ",";
									string collarB = to_string(static_cast<PlayerInfo*>(peer->data)->collarB);
									string R2 = to_string(static_cast<PlayerInfo*>(peer->data)->capeR2) + ",";
									string G2 = to_string(static_cast<PlayerInfo*>(peer->data)->capeG2) + ",";
									string B2 = to_string(static_cast<PlayerInfo*>(peer->data)->capeB2);
									string collarR2 = to_string(static_cast<PlayerInfo*>(peer->data)->collarR2) + ",";
									string collarG2 = to_string(static_cast<PlayerInfo*>(peer->data)->collarG2) + ",";
									string collarB2 = to_string(static_cast<PlayerInfo*>(peer->data)->collarB2);
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_starfieldaura == 1) {
										starfield = "1";
									}
									else {
										starfield = "0";
									}
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_portalaura == 1) {
										portal = "1";
									}
									else {
										portal = "0";
									}
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_electricalaura == 1) {
										electrical = "1";
									}
									else {
										electrical = "0";
									}
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_auraonoff == 1) {
										auraonoff = "1";
									}
									else {
										auraonoff = "0";
									}
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_capecollar == 1) {
										capecollar = "1";
									}
									else {
										capecollar = "0";
									}
									if (static_cast<PlayerInfo*>(peer->data)->checkbox_timedilation == 1) {
										Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wRift Cape|left|10424|\nadd_spacer|small|\nadd_text_input|timedilation|Time Dilation Cycle Time:|" + to_string(static_cast<PlayerInfo*>(peer->data)->timedilation) + "|6|\nadd_checkbox|checkbox_timedilation|Time Dilation On / Off|1\nadd_button|instructions|Instructions|\nadd_spacer|small|\nadd_label|big|Cape Style 1|\nadd_spacer|small|\nadd_textbox|Cape Color:|left|\nadd_text_input|capergb|Cape - R,G,B:|" + R + G + B + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_capecollar|Cape Collar On / Off|" + capecollar + "|\nadd_textbox|Cape Collar Color:|\nadd_text_input|collarrgb|Collar - R,G,B:|" + collarR + collarG + collarB + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_closedcape|Closed Cape|" + to_string(static_cast<PlayerInfo*>(peer->data)->checkbox_closedcape) + "\nadd_checkbox|checkbox_opencapemovement|Open Cape on Movement|" + to_string(static_cast<PlayerInfo*>(peer->data)->checkbox_opencapemovement) + "\nadd_checkbox|checkbox_auraonoff|Aura On / Off|" + auraonoff + "\nadd_checkbox|checkbox_portalaura|Portal Aura|" + portal + "\nadd_checkbox|checkbox_starfieldaura|Starfield Aura|" + starfield + "\nadd_checkbox|checkbox_electricalaura|Electrical Aura|" + electrical + "\nadd_button|restoretodefault|Restore to Default|\nend_dialog|riftcape|Close|`wUpdate|\nadd_quick_exit|\n");
									}
									else {
										Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wRift Cape|left|10424|\nadd_spacer|small|\nadd_text_input|timedilation|Time Dilation Cycle Time:|" + to_string(static_cast<PlayerInfo*>(peer->data)->timedilation) + "|6|\nadd_checkbox|checkbox_timedilation|Time Dilation On / Off|0\nadd_button|instructions|Instructions|\nadd_spacer|small|\nadd_label|big|Cape Style 1|\nadd_spacer|small|\nadd_textbox|Cape Color:|left|\nadd_text_input|capergb|Cape - R,G,B:|" + R + G + B + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_capecollar|Cape Collar On / Off|" + capecollar + "|\nadd_textbox|Cape Collar Color:|\nadd_text_input|collarrgb|Collar - R,G,B:|" + collarR + collarG + collarB + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_closedcape|Closed Cape|" + to_string(static_cast<PlayerInfo*>(peer->data)->checkbox_closedcape) + "\nadd_checkbox|checkbox_opencapemovement|Open Cape on Movement|" + to_string(static_cast<PlayerInfo*>(peer->data)->checkbox_opencapemovement) + "\nadd_checkbox|checkbox_auraonoff|Aura On / Off|" + auraonoff + "\nadd_checkbox|checkbox_portalaura|Portal Aura|" + portal + "\nadd_checkbox|checkbox_starfieldaura|Starfield Aura|" + starfield + "\nadd_checkbox|checkbox_electricalaura|Electrical Aura|" + electrical + "\nadd_button|restoretodefault|Restore to Default|\nend_dialog|riftcape|Close|`wUpdate|\nadd_quick_exit|\n");
									}
								}
//here
if (btn == "instructions") {
									Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`oInstruction``|left|10424|\nadd_spacer|small|\nadd_textbox|`oUse RGB for setting a color (RED, GREEN, BLUE), portal aura for effect like portal, electrical aura for effect like electric.|0|0|\nadd_quick_exit|\n\nend_dialog|gazette|`oClose||");
								}
								if (btn == "editriftcape") {
									string starfield = "0";
									string portal = "0";
									string electrical = "0";
									string auraonoff = "0";
									string capecollar = "0";
									string R = to_string(pdata(peer)->capeR) + ",";
									string G = to_string(pdata(peer)->capeG) + ",";
									string B = to_string(pdata(peer)->capeB);
									string collarR = to_string(pdata(peer)->collarR) + ",";
									string collarG = to_string(pdata(peer)->collarG) + ",";
									string collarB = to_string(pdata(peer)->collarB);
									string R2 = to_string(pdata(peer)->capeR2) + ",";
									string G2 = to_string(pdata(peer)->capeG2) + ",";
									string B2 = to_string(pdata(peer)->capeB2);
									string collarR2 = to_string(pdata(peer)->collarR2) + ",";
									string collarG2 = to_string(pdata(peer)->collarG2) + ",";
									string collarB2 = to_string(pdata(peer)->collarB2);
									if (pdata(peer)->checkbox_starfieldaura == 1) {
										starfield = "1";
									}
									else {
										starfield = "0";
									}
									if (pdata(peer)->checkbox_portalaura == 1) {
										portal = "1";
									}
									else {
										portal = "0";
									}
									if (pdata(peer)->checkbox_electricalaura == 1) {
										electrical = "1";
									}
									else {
										electrical = "0";
									}
									if (pdata(peer)->checkbox_auraonoff == 1) {
										auraonoff = "1";
									}
									else {
										auraonoff = "0";
									}
									if (pdata(peer)->checkbox_capecollar == 1) {
										capecollar = "1";
									}
									else {
										capecollar = "0";
									}
									if (pdata(peer)->checkbox_timedilation == 1) {
										Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wRift Cape|left|10424|\nadd_spacer|small|\nadd_text_input|timedilation|Time Dilation Cycle Time:|" + to_string(pdata(peer)->timedilation) + "|6|\nadd_checkbox|checkbox_timedilation|Time Dilation On / Off|1\nadd_button|instructions|Instructions|\nadd_spacer|small|\nadd_label|big|Cape Style 1|\nadd_spacer|small|\nadd_textbox|Cape Color:|left|\nadd_text_input|capergb|Cape - R,G,B:|" + R + G + B + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_capecollar|Cape Collar On / Off|" + capecollar + "|\nadd_textbox|Cape Collar Color:|\nadd_text_input|collarrgb|Collar - R,G,B:|" + collarR + collarG + collarB + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_closedcape|Closed Cape|" + to_string(pdata(peer)->checkbox_closedcape) + "\nadd_checkbox|checkbox_opencapemovement|Open Cape on Movement|" + to_string(pdata(peer)->checkbox_opencapemovement) + "\nadd_checkbox|checkbox_auraonoff|Aura On / Off|" + auraonoff + "\nadd_checkbox|checkbox_portalaura|Portal Aura|" + portal + "\nadd_checkbox|checkbox_starfieldaura|Starfield Aura|" + starfield + "\nadd_checkbox|checkbox_electricalaura|Electrical Aura|" + electrical + "\nadd_button|restoretodefault|Restore to Default|\nend_dialog|riftcape|Close|`wUpdate|\nadd_quick_exit|\n");
									}
									else {
										Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wRift Cape|left|10424|\nadd_spacer|small|\nadd_text_input|timedilation|Time Dilation Cycle Time:|" + to_string(pdata(peer)->timedilation) + "|6|\nadd_checkbox|checkbox_timedilation|Time Dilation On / Off|0\nadd_button|instructions|Instructions|\nadd_spacer|small|\nadd_label|big|Cape Style 1|\nadd_spacer|small|\nadd_textbox|Cape Color:|left|\nadd_text_input|capergb|Cape - R,G,B:|" + R + G + B + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_capecollar|Cape Collar On / Off|" + capecollar + "|\nadd_textbox|Cape Collar Color:|\nadd_text_input|collarrgb|Collar - R,G,B:|" + collarR + collarG + collarB + "|12|\nadd_spacer|small|\nadd_checkbox|checkbox_closedcape|Closed Cape|" + to_string(pdata(peer)->checkbox_closedcape) + "\nadd_checkbox|checkbox_opencapemovement|Open Cape on Movement|" + to_string(pdata(peer)->checkbox_opencapemovement) + "\nadd_checkbox|checkbox_auraonoff|Aura On / Off|" + auraonoff + "\nadd_checkbox|checkbox_portalaura|Portal Aura|" + portal + "\nadd_checkbox|checkbox_starfieldaura|Starfield Aura|" + starfield + "\nadd_checkbox|checkbox_electricalaura|Electrical Aura|" + electrical + "\nadd_button|restoretodefault|Restore to Default|\nend_dialog|riftcape|Close|`wUpdate|\nadd_quick_exit|\n");
									}
								}
