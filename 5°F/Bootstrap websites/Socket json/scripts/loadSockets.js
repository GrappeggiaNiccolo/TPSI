document.addEventListener("DOMContentLoaded", async () => {
    try {
        // Caricamento dei dati dal file JSON
        const response = await fetch('json/socketsContent.json');
        if (!response.ok) throw new Error("Impossibile caricare il file JSON");
        const pageContent = await response.json();

        // Popolamento della sezione Hero
        const hero = document.getElementById("hero-section");
        if (hero) {
            hero.innerHTML = `
                <div class="container">
                    <h1>${pageContent.hero.title}</h1>
                    <p class="lead">${pageContent.hero.subtitle}</p>
                </div>
            `;
        }

        // Popolamento della sezione Definition
        const definitionSection = document.getElementById("definition-section");
        if (definitionSection) {
            definitionSection.innerHTML = `
                <div class="col-md-6">
                    <h2>${pageContent.definition.title}</h2>
                    <p>${pageContent.definition.text}</p>
                </div>
                <div class="col-md-6">
                    <img src="${pageContent.definition.image}" class="img-fluid rounded" alt="Immagine socket">
                </div>
            `;
        }

        // Popolamento della sezione Socket Types
        const typesSection = document.getElementById("socket-types-section");
        if (typesSection) {
            typesSection.innerHTML = `
                <h2 class="text-center">Tipi di Socket</h2>
                <div class="row justify-content-center">
                    ${pageContent.socketTypes.map(type => `
                        <div class="col-md-5">
                            <div class="card mb-4 shadow-sm">
                                <div class="card-body">
                                    <h5 class="card-title">${type.title}</h5>
                                    <p class="card-text">${type.text}</p>
                                </div>
                            </div>
                        </div>
                    `).join('')}
                </div>
            `;
        }

        // Popolamento della sezione Client-Server
        const clientServerSection = document.getElementById("client-server-section");
        if (clientServerSection) {
            clientServerSection.innerHTML = `
                <h2 class="text-center mb-4">Socket nel Modello Client-Server</h2>
                <div class="row align-items-center">
                    <div class="col-md-5">
                        <img src="${pageContent.clientServer.image}" class="img-fluid rounded shadow" alt="Modello client-server">
                    </div>
                    <div class="col-md-7">
                        <div class="p-4 rounded shadow-sm">
                            <p>${pageContent.clientServer.text}</p>
                            <div class="row">
                                ${pageContent.clientServer.applications.map(app => `
                                    <div class="col-6">
                                        <ul class="list-group">
                                            <li class="list-group-item">
                                                <i class="bi ${app[1]}"></i> ${app[0]}
                                            </li>
                                        </ul>
                                    </div>
                                `).join('')}
                            </div>
                        </div>
                    </div>
                </div>
            `;
        }
    } catch (error) {
        console.error("Errore nel caricamento dei contenuti:", error);
    }
});
