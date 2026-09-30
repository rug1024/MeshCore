# T-Beam 1W Ruhrgebiet factory defaults

Applies to `LilyGo_TBeam_1W_repeater` with `DMC_RUHR_DEFAULTS`.
Includes the fan fix and 1700 us PA ramp fix.

- Coding rate: 8 (4/8)
- Local advert interval: 240 minutes
- Flood advert interval: 24 hours
- Flood limits (general, unscoped, adverts): 8 hops
- CAD and boosted RX gain: on
- Minimum path hash size: 1 byte
- Packet filter: on, with these 16 blocked channels:
  #test, #testkanal, #ping, #pingpong, #wardriving, #meshoe, #bot, #mc-radar, #bauerbahn, #bergischesland, #koeln, #bonn, #limburg, #muenster, #detmold, #lohmar
- Regions: `* -> de -> de-nw -> ruhrgebiet`
- Flood denied: `*`, `de`
- Flood allowed: `de-nw`, `ruhrgebiet`
- Home and default region: `ruhrgebiet`
- Automatic boot advert: disabled on every boot, including a fresh flash.
- Regular scheduled adverts still occur after 240 minutes / 24 hours.
- Manual adverts remain available.
- Battery measurement is unchanged.

Existing node preferences, region maps and filter preferences take precedence
on firmware updates. These are factory defaults, not a migration that rewrites
configured devices. Missing region/filter files are initialized and saved once.
`filter reset` restores this profile's enabled filter and complete blocklist.
Channel blocking retains DMC's existing hash-based GRP_TXT forwarding semantics,
including direct-route and priority exceptions. Other filter settings retain
DMC's defaults. All 16 channel slots are occupied by this profile.
