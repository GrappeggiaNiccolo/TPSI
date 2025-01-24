document.addEventListener("DOMContentLoaded", () => {
    fetch("data.json")
        .then(response => response.json())
        .then(data => {
            const path = window.location.pathname;

            if (path.includes("index.html")) {
                // Archivio Prodotti
                document.getElementById("title").textContent = data.archive.title;
                const productList = document.getElementById("product-list");
                data.archive.products.forEach(product => {
                    const productDiv = document.createElement("div");
                    productDiv.className = "product";
                    productDiv.innerHTML = `
                        <h2>${product.name}</h2>
                        <p>${product.description}</p>
                        <p>${product.price}</p>
                        <a href="product.html?id=${product.id}">Dettagli</a>
                    `;
                    productList.appendChild(productDiv);
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
                        <h2>${product.name}</h2>
                        <p>${product.description}</p>
                        <p>${product.price}</p>
                        <button>Aggiungi al carrello</button>
                    `;
                }
            } else if (path.includes("cart.html")) {
                // Carrello
                document.getElementById("cart-title").textContent = data.cart.title;
                const cartItems = document.getElementById("cart-items");
                data.cart.items.forEach(item => {
                    const itemDiv = document.createElement("div");
                    itemDiv.className = "cart-item";
                    itemDiv.innerHTML = `
                        <h2>${item.name}</h2>
                        <p>Quantità: ${item.quantity}</p>
                        <p>Prezzo: ${item.price}</p>
                    `;
                    cartItems.appendChild(itemDiv);
                });

                document.getElementById("cart-total").textContent = `Totale: ${data.cart.total}`;
            }

            // Footer
            document.getElementById("footer").textContent = data.footer;
        })
        .catch(error => console.error("Errore nel caricamento del JSON:", error));
});
