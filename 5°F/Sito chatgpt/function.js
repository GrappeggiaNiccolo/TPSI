// Variabile globale per il timer
let timerInterval;
let tempoRimanente = 10 * 60; // 10 minuti in secondi

// Inizializza il timer di 10 minuti
function avviaTimer() {
    const timerElement = document.getElementById('timer');
    timerInterval = setInterval(() => {
        if (tempoRimanente <= 0) {
            clearInterval(timerInterval);
            salvaInFile(); // Salva automaticamente le risposte alla fine
            alert("Tempo scaduto! Risposte salvate.");
            location.href = "index.html";
        } else {
            tempoRimanente--;
            timerElement.innerText = `${Math.floor(tempoRimanente / 60)}:${(tempoRimanente % 60).toString().padStart(2, '0')}`;
        }
    }, 1000);
}

// Carica domande dal file JSON
async function caricaDomande() {
    const response = await fetch('domande.json');
    return await response.json();
}

// Salva risposta nel LocalStorage
function salvaRisposta(id, risposta) {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    risposte[id] = risposta;
    localStorage.setItem('risposte', JSON.stringify(risposte));
    aggiornaContatore();
}

// Carica risposta dal LocalStorage
function caricaRisposta(id) {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    return risposte[id] || '';
}

// Aggiorna contatore delle risposte
function aggiornaContatore() {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    const totaleRisposte = Object.keys(risposte).length;
    document.getElementById('contatore').innerText = `${totaleRisposte}/5`;
}

// Navigazione tra domande
function vaiA(tipo, id) {
    if (tipo === 'aperta') {
        location.href = `domanda_aperta.html?id=${id}`;
    } else if (tipo === 'crocetta') {
        location.href = `crocetta.html?id=${id}`;
    }
}

// Salvataggio automatico della risposta
function salvaRispostaAutomatica(tipo) {
    const id = new URLSearchParams(window.location.search).get('id');
    let risposta;
    if (tipo === 'aperta') {
        risposta = document.getElementById('risposta').value;
    } else if (tipo === 'crocetta') {
        risposta = document.querySelector('input[name=risposta]:checked')?.value;
    }
    salvaRisposta(id, risposta);
}

// Inizializza pagina con navigazione e caricamento risposte
async function inizializzaPagina(tipo) {
    const id = parseInt(new URLSearchParams(window.location.search).get('id')) || new URLSearchParams(window.location.search).get('id');
    const domande = await caricaDomande();
    let domanda, indice;

    if (tipo === 'aperta') {
        domanda = domande.domande_aperta.find(d => d.id === parseInt(id));
        indice = domande.domande_aperta.findIndex(d => d.id === parseInt(id));
        if (!domanda) {
            alert("Domanda non trovata!");
            return;
        }
        document.getElementById('domanda').innerText = domanda.testo;
        document.getElementById('risposta').value = caricaRisposta(id);
        document.getElementById('risposta').addEventListener('input', () => salvaRispostaAutomatica(tipo));
    } else if (tipo === 'crocetta') {
        domanda = domande.domande_crocetta.find(d => d.id === id);
        indice = domande.domande_crocetta.findIndex(d => d.id === id);
        if (!domanda) {
            alert("Domanda non trovata!");
            return;
        }
        document.getElementById('domanda').innerText = domanda.testo;

        // Carica opzioni di risposta
        const opzioniContainer = document.getElementById('opzioni');
        opzioniContainer.innerHTML = '';
        domanda.opzioni.forEach(opzione => {
            const radio = document.createElement('input');
            radio.type = 'radio';
            radio.name = 'risposta';
            radio.value = opzione;
            if (opzione === caricaRisposta(id)) radio.checked = true;
            radio.addEventListener('change', () => salvaRispostaAutomatica(tipo));

            const label = document.createElement('label');
            label.innerText = opzione;
            opzioniContainer.appendChild(radio);
            opzioniContainer.appendChild(label);
            opzioniContainer.appendChild(document.createElement('br'));
        });
    }

    configuraNavigazione(tipo, indice, domande);
}

// Configurazione dei pulsanti di navigazione
function configuraNavigazione(tipo, indice, domande) {
    const precedenteButton = document.getElementById('precedente');
    const successivoButton = document.getElementById('successivo');

    const listaDomande = tipo === 'aperta' ? domande.domande_aperta : domande.domande_crocetta;

    if (indice > 0) {
        const domandaPrecedente = listaDomande[indice - 1];
        const nuovoTipo = domandaPrecedente.id <= 3 ? 'aperta' : 'crocetta';
        precedenteButton.onclick = () => vaiA(nuovoTipo, domandaPrecedente.id);
        precedenteButton.disabled = false;
    } else {
        precedenteButton.disabled = true;
    }

    if (indice < listaDomande.length - 1) {
        const domandaSuccessiva = listaDomande[indice + 1];
        const nuovoTipo = domandaSuccessiva.id <= 3 ? 'aperta' : 'crocetta';
        successivoButton.onclick = () => vaiA(nuovoTipo, domandaSuccessiva.id);
        successivoButton.disabled = false;
    } else {
        successivoButton.disabled = true;
    }
}
