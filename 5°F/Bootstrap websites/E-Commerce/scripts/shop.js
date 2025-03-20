document.addEventListener("DOMContentLoaded", () => {
    fetch("data/data.json")
        .then(response => response.json())
        .then(data => {
            const cardsContainer = document.getElementById("cards");
            
            cardsContainer.innerHTML = data.archive.products.map(product => `
                <div class="col-md-4 mb-4">
                    <div class="card h-100 shadow-sm">
                        <img src="${product.image}" class="card-img-top" alt="${product.name}">
                        <div class="card-body text-center">
                            <h5 class="card-title">${product.name}</h5>
                            <p class="card-text">${product.description}</p>
                            <p class="fw-bold">${product.price}</p>
                            <a href="product.html?id=${product.id}" class="btn btn-primary">Dettagli</a>
                        </div>
                    </div>
                </div>
            `).join("");
        })
        .catch(error => console.error("Errore nel caricamento dei prodotti:", error));
});
