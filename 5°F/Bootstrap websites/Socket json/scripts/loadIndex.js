document.addEventListener("DOMContentLoaded", async () => {
    try {
        // Caricamento dei dati dal file JSON
        const response = await fetch('json/indexContent.json');
        if (!response.ok) throw new Error("Impossibile caricare il file JSON");
        const pageContent = await response.json();

        // Popolamento della sezione Hero
        const hero = document.getElementById('hero');
        hero.innerHTML = `
            <div class="container">
                <h1>${pageContent.hero.title}</h1>
                <p class="lead">${pageContent.hero.subtitle}</p>
                <a href="${pageContent.hero.buttonLink}" class="btn btn-light btn-lg mt-3">${pageContent.hero.buttonText}</a>
            </div>
        `;

        // Popolamento della sezione Accordion
        const accordion = document.getElementById('accordion');
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

        // Popolamento della sezione Cards
        const cards = document.getElementById('cards');
        cards.innerHTML = pageContent.cards.map(card => `
            <div class="col-md-4">
                <div class="card">
                    <img src="${card.image}" class="card-img-top" alt="${card.title}">
                    <div class="card-body text-center">
                        <h5 class="card-title">${card.title}</h5>
                        <p class="card-text">${card.text}</p>
                        <a href="${card.link}" class="btn btn-primary">Leggi di più</a>
                    </div>
                </div>
            </div>
        `).join('');
    } catch (error) {
        console.error("Errore nel caricamento dei contenuti:", error);
    }
});
