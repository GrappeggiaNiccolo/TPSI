document.addEventListener("DOMContentLoaded", () => {
    // Hero Section
    const hero = document.getElementById("hero-section");
    if (hero) {
        hero.innerHTML = `
            <div class="container">
                <h1>${pageContent.hero.title}</h1>
                <p class="lead">${pageContent.hero.subtitle}</p>
            </div>
        `;
    }

    // Definition Section
    const definitionSection = document.getElementById("definition-section");
    if (definitionSection && pageContent.definition) {
        definitionSection.innerHTML = `
            <div class="col-md-6">
                <h2>${pageContent.definition.title}</h2>
                <p>${pageContent.definition.text}</p>
            </div>
            <div class="col-md-6">
                <img src="${pageContent.definition.image}" class="img-fluid rounded" alt="Immagine socket">
            </div>
        `;
    } else {
        console.error("Element not found: #definition-section or pageContent.definition is missing");
    }

    // Socket Types Section
    const typesSection = document.getElementById("socket-types-section");
    if (typesSection && pageContent.socketTypes) {
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

    // Client-Server Section
    const clientServerSection = document.getElementById("client-server-section");
    if (clientServerSection && pageContent.clientServer) {
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
});
