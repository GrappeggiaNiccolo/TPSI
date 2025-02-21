document.addEventListener("DOMContentLoaded", () => {
    fetch('data/data.json')
        .then(response => response.json())
        .then(data => {
            // Imposta il titolo
            const archiveHeading = document.querySelector("main h2");
            archiveHeading.textContent = data.archive.title;

            // Seleziona il contenitore delle cards
            const cardsContainer = document.getElementById("cards");
            cardsContainer.innerHTML = ""; // Pulisce prima di aggiungere

            data.archive.products.forEach(product => {
                const col = document.createElement("div");
                col.classList.add("col-md-4"); // Aggiunge classe correttamente
                col.innerHTML = `
                    <div class="card h-100">
                        <img src="${product.image}" class="card-img-top" alt="${product.name}">
                        <div class="card-body text-center">
                            <h5 class="card-title">${product.name}</h5>
                            <p class="card-text">${product.description}</p>
                            <a href="product.html?id=${product.id}" class="btn btn-primary">Dettagli</a>
                            <button class="btn btn-success">Aggiungi al carrello</button>
                        </div>
                    </div>
                `;
                cardsContainer.appendChild(col); // Aggiunge al contenitore
            });

            // Imposta il footer
            const footer = document.getElementById("footer-placeholder");
            footer.textContent = data.footer;
        })
        .catch(error => console.log('Errore nel caricare i dati:', error));
});

