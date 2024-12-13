// dynamic-content.js

// Funzione per inserire i contenuti dinamicamente
window.onload = function () {
    // Sezione titolo
    const titleSection = document.getElementById("title-section");
    titleSection.innerHTML = `
        <h1 class="display-5">${tcpUdpData.titleSection.title}</h1>
        <p class="lead text-muted">${tcpUdpData.titleSection.description}</p>
    `;

    // Sezione introduzione
    const introSection = document.getElementById("intro-section");
    introSection.innerHTML = `
        <h2 class="h4">${tcpUdpData.introSection.title}</h2>
        <p>${tcpUdpData.introSection.description}</p>
    `;

    // Sezione protocolli
const protocolsSection = document.getElementById("protocols-section");

let protocolsContent = tcpUdpData.protocols.map(protocol => `
    <div class="col-md-6 mb-4">
        <div class="card">
            <div class="card-header ${protocol.title === "TCP (Transmission Control Protocol)" ? 'bg-info text-white' : 'bg-warning text-dark'}">
                <h5 class="card-title">${protocol.title}</h5>
            </div>
            <div class="card-body">
                <ul>
                    ${protocol.characteristics.map(char => `<li><strong>${char.split(':')[0]}:</strong> ${char.split(':')[1]}</li>`).join('')}
                </ul>
            </div>
        </div>
    </div>
`).join('');

// Inserisci il contenuto nella sezione
protocolsSection.innerHTML = `
    <h2 class="h4 text-center">Confronto tra TCP e UDP</h2>
    <div class="row">${protocolsContent}</div>
`;


    // Sezione tabella comparativa
    const comparisonTableSection = document.getElementById("comparison-table");
    let tableRows = '';
    tcpUdpData.comparisonTable.forEach(row => {
        tableRows += `
            <tr>
                <td>${row.feature}</td>
                <td>${row.tcp}</td>
                <td>${row.udp}</td>
            </tr>
        `;
    });
    comparisonTableSection.innerHTML = `
        <h2 class="h4 text-center">Tabella Comparativa</h2>
        <table class="table table-bordered table-striped">
            <thead>
                <tr>
                    <th>Caratteristica</th>
                    <th>TCP</th>
                    <th>UDP</th>
                </tr>
            </thead>
            <tbody>
                ${tableRows}
            </tbody>
        </table>
    `;
};
