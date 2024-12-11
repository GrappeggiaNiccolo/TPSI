document.addEventListener("DOMContentLoaded", () => {
    // Carica il titolo della pagina
    const pageTitle = document.getElementById('page-title');
    pageTitle.innerHTML = pageContent.hero.title;

    // Carica la sezione Hero
    const heroTitle = document.getElementById('hero-title');
    const heroSubtitle = document.getElementById('hero-subtitle');

    heroTitle.innerHTML = pageContent.hero.title;
    heroSubtitle.innerHTML = pageContent.hero.subtitle;

    // Carica la sezione Introduzione
    const intro = document.getElementById('intro');
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

    // Carica titolo accordion
    const accordionTitle = document.getElementById('accordion-title');
    accordionTitle.innerHTML = pageContent.accordionTitle || "Livelli del modello ISO/OSI";

    // Carica la sezione Accordion
    const accordion = document.getElementById('osiAccordion');
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
});
