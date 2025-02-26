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
            cardsContainer.innerHTML = ""; // Pulisce prima di aggiungere

            data.archive.products.forEach(product => {
                const col = document.createElement("div");
                col.classList.add("col-md-4");
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
                cardsContainer.appendChild(col);
            });
        })
        .catch(error => console.log('Errore nel caricare i prodotti:', error));
});
