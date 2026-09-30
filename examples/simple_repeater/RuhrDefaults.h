#pragma once

#include <stdint.h>
#include <helpers/RegionMap.h>

// Factory profile for the T-Beam 1W DMC repeater.
// Applied before saved preferences are loaded, never over a saved configuration.
namespace RuhrDefaults {
static constexpr const char* blocked_channels[] = {
  "#test",
  "#testkanal",
  "#ping",
  "#pingpong",
  "#wardriving",
  "#meshoe",
  "#bot",
  "#mc-radar",
  "#bauerbahn",
  "#bergischesland",
  "#koeln",
  "#bonn",
  "#limburg",
  "#muenster",
  "#detmold",
  "#lohmar"
};

template<class Prefs>
void applyNodePrefs(Prefs& prefs) {
  prefs.cr = 8;
  prefs.advert_interval = 120;       // stored in two-minute units: 240 minutes
  prefs.flood_advert_interval = 24;  // hours
  prefs.flood_max = 8;
  prefs.flood_max_unscoped = 8;
  prefs.flood_max_advert = 8;
  prefs.cad_enabled = 1;
  prefs.rx_boosted_gain = 1;
}

template<class Regions>
bool initializeRegions(Regions& regions) {
  regions.getWildcard().flags |= REGION_DENY_FLOOD;
  auto de = regions.putRegion("de", 0);
  if (!de) return false;
  de->flags |= REGION_DENY_FLOOD;
  auto nw = regions.putRegion("de-nw", de->id);
  if (!nw) return false;
  nw->flags &= ~REGION_DENY_FLOOD;
  auto home = regions.putRegion("ruhrgebiet", nw->id);
  if (!home) return false;
  home->flags &= ~REGION_DENY_FLOOD;
  regions.setHomeRegion(home);
  regions.setDefaultRegion(home);
  return true;
}
}
