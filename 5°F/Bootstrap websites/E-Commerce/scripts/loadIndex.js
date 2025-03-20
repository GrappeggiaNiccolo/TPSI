document.addEventListener("DOMContentLoaded", () => {
    // Carica i contenuti della pagina
    fetch('data/indexData.json')
        .then(response => response.json())
        .then(data => {
            // Imposta il titolo dell'hero section
            document.querySelector("#hero h1").textContent = data.hero.title;
            document.querySelector("#hero p").textContent = data.hero.subtitle;

            // Imposta il titolo della sezione prodotti
            document.querySelector("main h2").textContent = data.archive.title;
        })
        .catch(error => console.log('Errore nel caricare i dati della pagina:', error));

    // Carica i prodotti in anteprima
    fetch('data/data.json')
        .then(response => response.json())
        .then(data => {
            const cardsContainer = document.getElementById("cards");
            cardsContainer.innerHTML = ""; // Pulisce il contenitore

            // Ordina i prodotti dal più costoso al più economico
            const sortedProducts = data.archive.products
                .map(product => ({
                    ...product,
                    priceNum: parseFloat(product.price.replace("€", "").trim()) // Converte il prezzo in numero
                }))
                .sort((a, b) => b.priceNum - a.priceNum) // Ordina dal più alto al più basso
                .slice(0, 3); // Prende solo i primi 3 prodotti

            // Mostra i 3 prodotti più costosi
            sortedProducts.forEach(product => {
                const col = document.createElement("div");
                col.classList.add("col-md-4");
                col.innerHTML = `
                    <div class="card h-100">
                        <img src="${product.image}" class="card-img-top" alt="${product.name}">
                        <div class="card-body text-center">
                            <h5 class="card-title">${product.name}</h5>
                            <p class="card-text">${product.description}</p>
                            <p class="card-price"><strong>Prezzo: ${product.price}</strong></p>
                            <a href="product.html?id=${product.id}" class="btn btn-primary">Dettagli</a>
                        </div>
                    </div>
                `;
                cardsContainer.appendChild(col);
            });
        })
        .catch(error => console.log('Errore nel caricare i prodotti:', error));
});
