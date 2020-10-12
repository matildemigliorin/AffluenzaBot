# AffluenzaBot
Il prototipo si propone come strumento di conteggio dell'affluenza ad un seggio.

**Composizione**
 - Arduino MKR WiFi 1010 Board
 - Grove RGB LED Ring (20 -WS2813 Mini)
 - Grove OLED DIsplay 0.96" (SSD1315)
 - Node-RED
 - Telegram bot


**Come funziona**

All'utente che sta per entrare a votare dentro il seggio, viene presentato un dispositivo (pc o telefono, preferibilmente non il proprio per questioni di anonimato) in cui è presente ed in funzione il bot. Compariranno 3 tipologie di interazione sotto forma di bottonoe:
- Registrami: da premere in questa fase appena descritta, ovvero prima di entrare dentro il seggio a votare
- Ho votato: da premere dopo essere entrati dentro il seggio ed aver quindi votato
- Esci: per uscire dall'azione di richiesta all'utente
Quando l'utente preme il bottone 'Registrami', il LED Ring potrebbe cambiare colore. Diventerà (o rimarrà) verde se dentro al seggio sono presenti contemporaneamente al più 3 persone, dunque si saturerebbe la capienza con l'utente entrante in questione. Diventerà invece rosso se, dopo che l'utente ha registrato la propria presenza al voto, il seggio è già momentaneamente occupato al massimo della sua capacità (con questo prototipo è stata impostata a 4 persone ma può essere facilmente cambiata modificando la variabile countprt all'interno del codice Arduino).
Contemporaneamente a queste azioni, l'AffluenzaBot invierà il valore del numero di persone che hanno registrato la propria presenza al seggio, dunque l'affluenza, che verrà stampato sull'OLED.


**Node-RED Flow**
![FlowAffluenzaBot](https://user-images.githubusercontent.com/59685328/95745943-478d4380-0c96-11eb-8fa3-83408e6114fa.png)

Nel flow di Node-RED sono stati usati principalmente:
- node-red-contrib-chatbot
- node-red-contrib-mqtt-broker
che hanno permesso, rispettivamente, di controllare l'AffluenzaBot e di collegarlo tramite il Mosca MQTT broker ad Arduino.
