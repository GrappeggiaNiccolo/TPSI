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

// Funzione per caricare la pagina di un prodotto
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

        // NON sovrascrivere lo stock se esiste già nel localStorage
        if (!(product.id in productsStock)) {
            productsStock[product.id] = product.stock;  // Solo se non esiste già
            localStorage.setItem("productsStock", JSON.stringify(productsStock)); // Salva lo stock iniziale
        }

        // Usa sempre lo stock aggiornato da localStorage
        document.getElementById("product-quantity").max = productsStock[product.id];
        document.getElementById("stock-info").textContent = `Disponibili: ${productsStock[product.id]}`;

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

        // 🛒 Evento "Aggiungi al Carrello"
        document.getElementById("add-to-cart").addEventListener("click", () => {
            addToCart(product, parseInt(quantityInput.value));
        });
    } else {
        document.querySelector("main").innerHTML = "<h2 class='text-danger'>Prodotto non trovato</h2>";
    }
}


// Funzione per aggiungere un prodotto al carrello
function addToCart(product, quantity) {
    let cart = JSON.parse(localStorage.getItem("cart")) || [];
    let productsStock = JSON.parse(localStorage.getItem("productsStock")) || {};

    if (quantity > productsStock[product.id]) {
        alert("Quantità non disponibile!");
        return;
    }

    const existingProduct = cart.find(item => item.id === product.id);
    if (existingProduct) {
        existingProduct.quantity += quantity;
    } else {
        cart.push({ ...product, quantity });
    }

    productsStock[product.id] -= quantity;

    localStorage.setItem("cart", JSON.stringify(cart));
    localStorage.setItem("productsStock", JSON.stringify(productsStock));

    alert("Prodotto aggiunto al carrello!");
    document.getElementById("stock-info").textContent = `Disponibili: ${productsStock[product.id]}`;
}

// Funzione per caricare il carrello
function loadCart() {
    let cart = JSON.parse(localStorage.getItem("cart")) || [];
    let cartItems = document.getElementById("cart-items");
    let total = 0;

    cartItems.innerHTML = "";

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
            return; // Blocca l'acquisto se il carrello è vuoto
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

// Funzione per caricare i prodotti nel carousel
function loadProductList(data) {
    document.querySelector("h2").textContent = data.archive.title; // Imposta il titolo della sezione

    const carouselItems = document.getElementById("carousel-items");

    // Prendi i primi 3 prodotti per il carosello
    const featuredProducts = data.archive.products.slice(0, 3);

    featuredProducts.forEach((product, index) => {
        const activeClass = index === 0 ? "active" : ""; // Solo il primo elemento deve essere attivo
        const item = document.createElement("div");
        item.className = `carousel-item ${activeClass}`;
        item.innerHTML = `
            <img src="${product.image}" class="d-block w-100" alt="${product.name}">
            <div class="carousel-caption d-none d-md-block bg-dark bg-opacity-50 p-3 rounded">
                <h5>${product.name}</h5>
                <p>${product.description}</p>
                <p class="fw-bold">${product.price}</p>
                <a href="product.html?id=${product.id}" class="btn btn-primary">Scopri di più</a>
            </div>
        `;
        carouselItems.appendChild(item);
    });
}

