 =============================================================
 WiFi Credentials Template
 Author Bruno Santos
 
 Copy this file to secrets.h and fill in your credentials.
 secrets.h is listed in .gitignore and will never be committed.
 =============================================================
#ifndef SECRETS_H
#define SECRETS_H

#define WIFI_SSID     your_network_name
#define WIFI_PASSWORD your_network_password

#endif
```

E confirma que o `.gitignore` na raiz do repo tem essa linha
```
secrets.h