#include <cassert>
#include <cstring>
#include "../../examples/simple_repeater/RuhrDefaults.h"

struct Prefs {
  int cr=0, advert_interval=0, flood_advert_interval=0, flood_max=0;
  int flood_max_unscoped=0, flood_max_advert=0, cad_enabled=0, rx_boosted_gain=0;
  float adc_multiplier=2.75f;
};
struct Entry { unsigned id=0, parent=0; unsigned char flags=0; const char* name="*"; };
struct Regions {
  Entry root, entries[3];
  int count=0;
  Entry* home=nullptr;
  Entry* def=nullptr;
  Entry& getWildcard() { return root; }
  Entry* putRegion(const char* name, unsigned parent) {
    if (count == 3) return nullptr;
    Entry* e=&entries[count++];
    e->id=count; e->parent=parent; e->name=name; e->flags=REGION_DENY_FLOOD;
    return e;
  }
  void setHomeRegion(Entry* e) { home=e; }
  void setDefaultRegion(Entry* e) { def=e; }
};
int main() {
  Prefs prefs;
  RuhrDefaults::applyNodePrefs(prefs);
  assert(prefs.cr==8 && prefs.advert_interval*2==240 && prefs.flood_advert_interval==24);
  assert(prefs.flood_max==8 && prefs.flood_max_unscoped==8 && prefs.flood_max_advert==8);
  assert(prefs.cad_enabled==1 && prefs.rx_boosted_gain==1);
  assert(prefs.adc_multiplier==2.75f);
  Regions r;
  assert(RuhrDefaults::initializeRegions(r));
  assert(r.count==3);
  assert(std::strcmp(r.entries[0].name,"de")==0);
  assert(std::strcmp(r.entries[1].name,"de-nw")==0);
  assert(std::strcmp(r.entries[2].name,"ruhrgebiet")==0);
  assert(r.entries[0].parent==0 && r.entries[1].parent==r.entries[0].id);
  assert(r.entries[2].parent==r.entries[1].id);
  assert(r.root.flags & REGION_DENY_FLOOD);
  assert(r.entries[0].flags & REGION_DENY_FLOOD);
  assert(!(r.entries[1].flags & REGION_DENY_FLOOD));
  assert(!(r.entries[2].flags & REGION_DENY_FLOOD));
  assert(r.home==&r.entries[2] && r.def==&r.entries[2]);
  const char* expected[] = {"#test","#testkanal","#ping","#pingpong","#wardriving","#meshoe","#bot","#mc-radar","#bauerbahn","#bergischesland","#koeln","#bonn","#limburg","#muenster","#detmold","#lohmar"};
  static_assert(sizeof(expected)==sizeof(RuhrDefaults::blocked_channels), "Channel count");
  for (unsigned i=0; i<16; ++i) {
    assert(std::strcmp(expected[i],RuhrDefaults::blocked_channels[i])==0);
    assert(std::strlen(expected[i])<32);
    for (unsigned j=0; j<i; ++j) assert(std::strcmp(expected[i],expected[j])!=0);
  }
}
