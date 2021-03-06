if (world->owner == "" || isWorldOwner(peer, world) || static_cast<PlayerInfo*>(peer->data)->adminLevel > 3) {
	if (world->items[x + (y * world->width)].foreground == 3528 && tile == 32) {// Made by swe
		Player::OnDialogRequest(peer, "add_label_with_icon|big|`oArt Canvas|left|3528|\nadd_spacer|small|\nadd_textbox|`oThe Canvas is " + GetItemDef(world->items[x + (y * world->width)].intdata).name + ". |\nadd_item_picker|paints|`oPaint Something|Select any item to Paint|\nadd_text_input|psign|Signed:|" + world->items[x + (y * world->width)].sign + "|100|\nend_dialog|painting|cancel|ok|");
		static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);


	}
}

if (ispaint) {
	if (infoDat[0] == "paints") pid = infoDat[1];
	if (infoDat[0] == "psign") psign = infoDat[1];
}
if (ispaint) {
	if (infoDat[0] == "psign")
	{
		if (pid != "" || psign != "") {

			psign = infoDat[1];
			PlayerInfo* pinfo = ((PlayerInfo*)(peer->data));
			int x = pinfo->wrenchedBlockLocation % world->width;
			int y = pinfo->wrenchedBlockLocation / world->width;
			string sign = psign;
			int id = atoi(pid.c_str());
			SendCanvasData(peer, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, x, y, id, sign);
			world->items[x + (y * world->width)].sign = sign;
			world->items[x + (y * world->width)].intdata = id;


		}
	}
}

bool ispaint = false;
string pid = "";
string psign = "";
else if (worldInfo->items[i].foreground == 3528) {
	int xx = i % xSize, yy = i / xSize;
	SendCanvasData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, xx, yy, worldInfo->items[i].intdata, worldInfo->items[i].sign);
}

void SendCanvasData(ENetPeer* peer, short fg, short bg, int x, int y, int item, string text) {

	byte* ExtendedData = new byte[15 + item + text.length()];
	int state = 0x0010000;
	int extendedLen = 15 + item + text.length();
	int TextLen = text.length();

	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;

	byte* raw = new byte[56 + 15 + item + TextLen];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);

	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x23;
	memcpy(ExtendedData + 9, &item, 4);
	memcpy(ExtendedData + 13, &TextLen, 2);
	memcpy(ExtendedData + 15, text.data(), TextLen);

	memcpy(raw + 56, ExtendedData, extendedLen);

	SendPacketRaw3(4, raw, 56 + 15 + item + TextLen, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData; // fix memleak by playingo


}
