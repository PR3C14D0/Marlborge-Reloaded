#pragma once
#include <iostream>
#include <cpr/cpr.h>

using namespace std;

class DiscordThings {
public:
	void SpamDiscordWebhook(string webhook, string msg, int quantity);
};