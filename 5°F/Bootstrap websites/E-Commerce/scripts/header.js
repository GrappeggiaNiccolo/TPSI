document.addEventListener("DOMContentLoaded", () => {
    // HTML per la Navbar
    const navbarHTML = `
        <nav class="navbar navbar-expand-lg navbar-light bg-light">
            <div class="container-fluid">
                <a class="navbar-brand" href="index.html">E-commerce</a>
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarNav">
                    <ul class="navbar-nav">
                        <li class="nav-item">
                            <a class="nav-link active" href="index.html">Home</a>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="shop.html">Shop</a>
                        </li>
                        <li class="nav-item">
                            <a class="nav-link" href="cart.html">Carrello</a>
                        </li>
                    </ul>
                    <button id="bd-theme" class="btn btn-outline-secondary ms-auto">
                        <i class="bi bi-sun-fill"></i>
                    </button>
                </div>
            </div>
        </nav>
    `;

    // HTML per il Footer
    const footerHTML = `
        <footer class="text-center">
            <div class="container">
                <p>Realizzato da Niccolò Grappeggia - Classe 5°F</p>
                <p>
                    <a href="https://github.com/GrappeggiaNiccolo/TPSI/tree/main/5%C2%B0F/Bootstrap%20websites/"
                        class="text-white" target="_blank">Github Repository</a>
                </p>
            </div>
        </footer>
    `;

    // Inserisci la Navbar nel placeholder
    const headerPlaceholder = document.getElementById("header-placeholder");
    if (headerPlaceholder) {
        headerPlaceholder.innerHTML = navbarHTML;
    }

    // Inserisci il Footer nel placeholder
    const footerPlaceholder = document.getElementById("footer-placeholder");
    if (footerPlaceholder) {
        footerPlaceholder.innerHTML = footerHTML;
    }
});
