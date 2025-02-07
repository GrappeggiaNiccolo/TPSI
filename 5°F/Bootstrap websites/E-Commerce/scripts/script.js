document.addEventListener("DOMContentLoaded", () => {
    fetch("data/data.json")
        .then(response => response.json())
        .then(data => {
            const path = window.location.pathname;

            if (path.includes("index.html")) {
                // Archivio Prodotti
                document.getElementById("title").textContent = data.archive.title;
                const productList = document.getElementById("product-list");

                data.archive.products.forEach(product => {
                    const col = document.createElement("div");
                    col.className = "col-md-4 mb-4";
                    col.innerHTML = `
                        <div class="card h-100 shadow-sm">
                            <img src="${product.image}" class="card-img-top" alt="${product.name}">
                            <div class="card-body">
                                <h5 class="card-title">${product.name}</h5>
                                <p class="card-text">${product.description}</p>
                                <p class="card-text fw-bold">${product.price}</p>
                                <a href="product.html?id=${product.id}" class="btn btn-primary">Dettagli</a>
                            </div>
                        </div>
                    `;
                    productList.appendChild(col);
                });

            } else if (path.includes("product.html")) {
                // Singolo Prodotto
                const queryParams = new URLSearchParams(window.location.search);
                const productId = queryParams.get("id");
                const product = data.archive.products.find(p => p.id == productId);

                if (product) {
                    document.getElementById("product-title").textContent = data.product.title;
                    const productDetails = document.getElementById("product-details");
                    productDetails.innerHTML = `
                        <img src="${product.image}" class="img-fluid mb-3" alt="${product.name}">
                        <h2>${product.name}</h2>
                        <p>${product.description}</p>
                        <p class="fw-bold">${product.price}</p>
                        <button class="btn btn-success">Aggiungi al carrello</button>
                    `;
                } else {
                    document.getElementById("product-details").innerHTML = `<p class="text-danger">Prodotto non trovato.</p>`;
                }

            } else if (path.includes("cart.html")) {
                // Carrello
                document.getElementById("cart-title").textContent = data.cart.title;
                const cartItems = document.getElementById("cart-items");
                let total = 0;

                data.cart.items.forEach(item => {
                    const row = document.createElement("tr");
                    const itemTotal = parseFloat(item.price.replace("€", "").trim()) * item.quantity;
                    total += itemTotal;

                    row.innerHTML = `
                        <td><img src="${item.image}" width="50" alt="${item.name}"></td>
                        <td>${item.name}</td>
                        <td>${item.quantity}</td>
                        <td>${item.price}</td>
                        <td>${itemTotal.toFixed(2)} €</td>
                        <td><button class="btn btn-danger btn-sm remove-item"><i class="fas fa-trash"></i></button></td>
                    `;

                    cartItems.appendChild(row);
                });

                document.getElementById("cart-total").textContent = `Totale: ${total.toFixed(2)} €`;

                // Rimuovi prodotto dal carrello
                document.querySelectorAll(".remove-item").forEach(button => {
                    button.addEventListener("click", (event) => {
                        event.target.closest("tr").remove();
                    });
                });
            }
        })
        .catch(error => console.error("Errore nel caricamento del JSON:", error));
});
