document.addEventListener("DOMContentLoaded", () => {
    fetch("data/data.json")
        .then(response => response.json())
        .then(data => {
            const path = window.location.pathname;
            const queryParams = new URLSearchParams(window.location.search);

            if (path.includes("product.html")) {
                loadProductPage(data, queryParams);
            } else if (path.includes("cart.html")) {
                loadCart();
            } else if (path.includes("index.html")) {
                loadProductList(data);
            }
        })
        .catch(error => console.error("Errore nel caricamento del JSON:", error));
});
function loadProductPage(data, queryParams) {
    const productId = queryParams.get("id");
    const product = data.archive.products.find(p => p.id == productId);

    if (product) {
        document.querySelector("img.img-fluid").src = product.image;
        document.querySelector("img.img-fluid").alt = product.name;
        document.getElementById("product-title").textContent = product.name;
        document.getElementById("product-description").textContent = product.description;
        document.getElementById("product-price").textContent = product.price;

        let productsStock = JSON.parse(localStorage.getItem("productsStock")) || {};

        if (!(product.id in productsStock)) {
            productsStock[product.id] = product.stock;
            localStorage.setItem("productsStock", JSON.stringify(productsStock));
        }

        document.getElementById("product-quantity").max = productsStock[product.id];
        document.getElementById("stock-info").textContent = `Disponibili: ${productsStock[product.id]}`;

        // Creazione dei pallini colorati
        const colorContainer = document.getElementById("color-options");
        colorContainer.innerHTML = ""; // Pulisce il container

        product.colors.forEach((color, index) => {
            const colorButton = document.createElement("div");
            colorButton.classList.add("color-circle");
            colorButton.style.backgroundColor = color;
            colorButton.dataset.color = color;
            if (index === 0) colorButton.classList.add("selected"); // Seleziona il primo colore di default

            colorButton.addEventListener("click", () => {
                document.querySelectorAll(".color-circle").forEach(btn => btn.classList.remove("selected"));
                colorButton.classList.add("selected");
            });

            colorContainer.appendChild(colorButton);
        });

        // Gestione quantità
        const quantityInput = document.getElementById("product-quantity");
        document.getElementById("increase-qty").addEventListener("click", () => {
            if (parseInt(quantityInput.value) < productsStock[product.id]) {
                quantityInput.value = parseInt(quantityInput.value) + 1;
            }
        });
        document.getElementById("decrease-qty").addEventListener("click", () => {
            if (parseInt(quantityInput.value) > 1) {
                quantityInput.value = parseInt(quantityInput.value) - 1;
            }
        });

        // Aggiungi al Carrello
        document.getElementById("add-to-cart").addEventListener("click", () => {
            const selectedColor = document.querySelector(".color-circle.selected").dataset.color;
            addToCart(product, parseInt(quantityInput.value), selectedColor);
        });
    } else {
        document.querySelector("main").innerHTML = "<h2 class='text-danger'>Prodotto non trovato</h2>";
    }
}

// Modifica della funzione addToCart per includere il colore selezionato
function addToCart(product, quantity, color) {
    let cart = JSON.parse(localStorage.getItem("cart")) || [];
    let productsStock = JSON.parse(localStorage.getItem("productsStock")) || {};

    if (quantity > productsStock[product.id]) {
        alert("Quantità non disponibile!");
        return;
    }

    const existingProduct = cart.find(item => item.id === product.id && item.color === color);
    if (existingProduct) {
        existingProduct.quantity += quantity;
    } else {
        cart.push({ ...product, quantity, color });
    }

    productsStock[product.id] -= quantity;

    localStorage.setItem("cart", JSON.stringify(cart));
    localStorage.setItem("productsStock", JSON.stringify(productsStock));

    alert(`Prodotto (${color}) aggiunto al carrello!`);
    document.getElementById("stock-info").textContent = `Disponibili: ${productsStock[product.id]}`;
}

// Funzione per caricare il carrello
function loadCart() {
    let cart = JSON.parse(localStorage.getItem("cart")) || [];
    let cartItems = document.getElementById("cart-items");
    let cartMessage = document.getElementById("cart-message");
    let total = 0;

    cartItems.innerHTML = "";

    if (cart.length === 0) {
        cartMessage.textContent = "Carrello vuoto, aggiungere un prodotto al carrello per completare il checkout";
        cartMessage.classList.remove("d-none"); // Mostra il messaggio
        return 0;
    } else {
        cartMessage.classList.add("d-none"); // Nasconde il messaggio se il carrello ha prodotti
    }

    cart.forEach(item => {
        const itemTotal = parseFloat(item.price.replace("€", "").trim()) * item.quantity;
        total += itemTotal;

        const row = document.createElement("tr");
        row.innerHTML = `
            <td><img src="${item.image}" width="50" alt="${item.name}"></td>
            <td>${item.name}</td>
            <td>${item.quantity}</td>
            <td>${item.price}</td>
            <td>${itemTotal.toFixed(2)} €</td>
            <td><button class="btn btn-danger btn-sm remove-item" data-id="${item.id}"><i class="fas fa-trash"></i></button></td>
        `;

        cartItems.appendChild(row);
    });

    document.getElementById("cart-total").textContent = `Totale: ${total.toFixed(2)} €`;

    document.querySelectorAll(".remove-item").forEach(button => {
        button.addEventListener("click", (event) => {
            removeFromCart(event.target.closest("button").dataset.id);
        });
    });

    // Quando si acquistano i prodotti, il carrello si svuota
    document.getElementById("cart-payment").addEventListener("click", (event) => {
        let cart = JSON.parse(localStorage.getItem("cart")) || [];

        if (cart.length === 0) {
            alert("Il carrello è vuoto! Aggiungi prodotti prima di procedere all'acquisto.");
            return 0; // Blocca l'acquisto se il carrello è vuoto
        }

        alert("I prodotti sono stati acquistati con successo!");
        localStorage.removeItem("cart");
        loadCart();
    });
}

// Funzione per rimuovere un prodotto dal carrello e ripristinare lo stock
function removeFromCart(productId) {
    let cart = JSON.parse(localStorage.getItem("cart")) || [];
    let productsStock = JSON.parse(localStorage.getItem("productsStock")) || {};

    const productToRemove = cart.find(item => item.id == productId);
    if (productToRemove) {
        productsStock[productId] += productToRemove.quantity;
        cart = cart.filter(item => item.id != productId);

        localStorage.setItem("cart", JSON.stringify(cart));
        localStorage.setItem("productsStock", JSON.stringify(productsStock));

        loadCart();
    }
}