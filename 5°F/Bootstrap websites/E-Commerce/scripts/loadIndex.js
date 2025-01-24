document.addEventListener("DOMContentLoaded", () => {
    // Carica i dati dal file JSON
    fetch('data.json')
        .then(response => response.json())
        .then(data => {
            // Carica il titolo dell'header
            const headerTitle = data.header.title;
            document.querySelector("#hero h1").textContent = headerTitle;

            // Carica il titolo della sezione prodotti
            const archiveTitle = data.archive.title;
            const archiveHeading = document.querySelector("main h2");
            archiveHeading.textContent = archiveTitle;

            // Carica i prodotti nella sezione "Archivio Prodotti"
            const cardsContainer = document.getElementById("cards");
            data.archive.products.forEach(product => {
                const col = document.createElement("div");
                col.className = "col-md-4 mb-4";
                col.innerHTML = `
                    <div class="card h-100 shadow-sm">
                        <div class="card-body">
                            <h5 class="card-title">${product.name}</h5>
                            <p class="card-text">${product.description}</p>
                            <p class="card-text fw-bold">${product.price}</p>
                            <a href="#" class="btn btn-primary">Dettagli</a>
                        </div>
                    </div>
                `;
                cardsContainer.appendChild(col);
            });

            // Carica il footer
            const footer = document.getElementById("footer-placeholder");
            footer.textContent = data.footer;
        })
        .catch(error => {
            console.error('Errore nel caricare i dati:', error);
        });
});
