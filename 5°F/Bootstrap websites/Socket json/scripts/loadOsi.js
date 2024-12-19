document.addEventListener("DOMContentLoaded", () => {
    // Funzione per caricare il contenuto da un file JSON
    const loadContent = async () => {
        try {
            const response = await fetch("json/osiContent.json");
            const pageContent = await response.json();

            // Carica il titolo della pagina
            document.getElementById("page-title").textContent = pageContent.hero.title;

            // Carica la sezione Hero
            document.getElementById("hero-title").textContent = pageContent.hero.title;
            document.getElementById("hero-subtitle").textContent = pageContent.hero.subtitle;

            // Carica la sezione Introduzione
            const intro = document.getElementById("intro");
            if (intro) {
                intro.innerHTML = `
                    <div class="row align-items-center">
                        <div class="col-md-4">
                            <img src="${pageContent.intro.image}" alt="ISO/OSI" class="img-fluid" style="max-width: 100%; height: auto;">
                        </div>
                        <div class="col-md-8">
                            <h2 class="h4">${pageContent.intro.title}</h2>
                            <p>${pageContent.intro.description}</p>
                            <p><strong>${pageContent.intro.levels.join('</strong>, <strong>')}</strong></p>
                        </div>
                    </div>
                `;
            }

            // Carica il titolo dell'accordion
            document.getElementById("accordion-title").textContent = pageContent.accordionTitle || "Livelli del modello ISO/OSI";

            // Carica la sezione Accordion
            const accordion = document.getElementById("osiAccordion");
            if (accordion) {
                accordion.innerHTML = pageContent.accordion.map((item, index) => `
                    <div class="accordion-item">
                        <h2 class="accordion-header" id="heading${index}">
                            <button class="accordion-button ${index === 0 ? '' : 'collapsed'}" type="button"
                                data-bs-toggle="collapse" data-bs-target="#collapse${index}"
                                aria-expanded="${index === 0}" aria-controls="collapse${index}">
                                ${item.title}
                            </button>
                        </h2>
                        <div id="collapse${index}" class="accordion-collapse collapse ${index === 0 ? 'show' : ''}"
                            aria-labelledby="heading${index}" data-bs-parent="#accordion">
                            <div class="accordion-body">${item.content}</div>
                        </div>
                    </div>
                `).join('');
            }
        } catch (error) {
            console.error("Errore nel caricamento del contenuto:", error);
        }
    };

    // Inizia il caricamento
    loadContent();
});
