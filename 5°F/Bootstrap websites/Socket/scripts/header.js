document.addEventListener("DOMContentLoaded", () => {
    const headerHTML = `
        <nav class="navbar navbar-expand-lg navbar-dark bg-dark sticky-top">
            <div class="container">
                <a class="navbar-brand" href="index.html">Socket Guide</a>
                <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarNav">
                    <ul class="navbar-nav ms-auto">
                        <li class="nav-item"><a class="nav-link" href="index.html">Home</a></li>
                        <li class="nav-item"><a class="nav-link" href="sockets.html">Socket</a></li>
                        <li class="nav-item"><a class="nav-link" href="osi.html">Modello OSI</a></li>
                        <li class="nav-item"><a class="nav-link" href="tcp-udp.html">TCP vs UDP</a></li>
                        <li class="nav-item"><a class="nav-link" href="glossary.html">Glossario</a></li>
                    </ul>
                    <button id="bd-theme" class="btn btn-outline-light ms-3" aria-label="Toggle theme">
                        <i class="bi bi-sun-fill"></i>
                    </button>
                </div>
            </div>
        </nav>
    `;
    document.getElementById("header-placeholder").innerHTML = headerHTML;
});
