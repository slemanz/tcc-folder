# 2.1. Confecção de Placas de Circuito Impresso

## 2.1.1. O que foi feito

A atividade compreendeu a confecção completa de placas de circuito impresso (PCIs) para o desenvolvimento de uma Unidade de Controle Eletrônico (ECU), abrangendo todas as fases do processo, desde a concepção inicial até a implementação final. O projeto envolveu tanto o desenvolvimento do esquemático quanto o design detalhado do layout da placa, considerando aspectos críticos como a integração de componentes e a compatibilidade entre sistemas. A implementação física contemplou tanto a fabricação quanto a montagem dos componentes, culminando em testes rigorosos de verificação. O processo foi conduzido seguindo metodologias padronizadas de desenvolvimento de hardware embarcado, garantindo a qualidade e confiabilidade do produto final. A documentação detalhada de cada etapa permitiu o acompanhamento sistemático do progresso do projeto.

Durante a fase de especificação, foram definidos os requisitos técnicos essenciais para a ECU, incluindo parâmetros como consumo de energia, velocidade de processamento e capacidade de memória. A seleção criteriosa dos componentes levou em consideração fatores como tolerância térmica, durabilidade e compatibilidade com o sistema integrado. O planejamento prévio incluiu também a definição de protocolos de comunicação e interfaces necessárias para a operação efetiva da placa. A equipe manteve um controle rigoroso de todas as especificações técnicas ao longo do desenvolvimento. Os critérios de seleção foram estabelecidos com base em padrões industriais reconhecidos.

A fase de prototipagem envolveu a criação de versões iniciais da placa para validação de conceitos e testes preliminares. Foram realizadas simulações detalhadas do comportamento elétrico e térmico dos componentes, permitindo identificar e corrigir possíveis problemas antes da fabricação em larga escala. O processo de validação incluiu análises de interferência eletromagnética e verificação de parâmetros críticos de funcionamento. Todas as modificações foram documentadas e incorporadas às especificações finais do projeto. A equipe realizou múltiplas iterações até alcançar o design otimizado.

## 2.1.2. Por que foi feito

O objetivo principal desta etapa do projeto foi desenvolver uma solução robusta e eficiente para a ECU, garantindo um desempenho consistente e confiável do sistema embarcado. A necessidade de um layout eficiente na PCI era crítica para evitar problemas de funcionamento que poderiam comprometer toda a aplicação, como ruídos eletromagnéticos, quedas de tensão e instabilidade térmica. A qualidade do design influencia diretamente na precisão e velocidade de processamento dos sinais, além da durabilidade geral do equipamento. A equipe priorizou a adoção de boas práticas de engenharia para minimizar riscos operacionais.

A implementação seguiu princípios fundamentais de engenharia de hardware, considerando aspectos como a distribuição adequada de energia, proteção contra surtos, e compatibilidade eletromagnética. O projeto levou em conta também requisitos de manutenibilidade e atualização futura, permitindo evoluções tecnológicas sem necessidade de redesenho completo. A equipe buscou equilibrar performance, custo e complexidade na escolha das soluções técnicas. Todos os parâmetros foram dimensionados considerando margens de segurança adequadas.

A metodologia adotada priorizou a modularidade do design, permitindo a substituição ou atualização de componentes específicos sem afetar o funcionamento global do sistema. Esta abordagem facilita também a depuração e manutenção futuras, reduzindo tempo e custos operacionais. A equipe considerou ainda aspectos de escalabilidade para possíveis expansões do sistema. A documentação técnica foi elaborada de forma a permitir a replicação e modificação do projeto por outros profissionais.

## 2.1.3. Como foi feito

O processo começou na fase de design, onde utilizamos o software Altium Designer para criar os esquemas elétricos e desenvolver o layout detalhado da placa. Foi realizada uma análise cuidadosa da disposição dos componentes, considerando aspectos como a proximidade entre elementos, fluxo térmico e trajetória das trilhas de conexão. A equipe implementou técnicas avançadas de routing para otimizar o uso do espaço disponível na placa. Foram estabelecidos critérios rigorosos para a seleção dos componentes baseados em especificações técnicas precisas.

Após a conclusão do design virtual, a fabricação da placa foi realizada por uma empresa especializada em PCBs, utilizando substrato FR-4 de alta qualidade. O processo de fotolitografia foi executado seguindo padrões industriais rigorosos, garantindo a precisão nas trilhas e vias. A equipe acompanhou todas as etapas do processo fabril, verificando a conformidade com as especificações técnicas estabelecidas. Foram realizadas inspeções visuais detalhadas após cada etapa do processo.

Na fase de montagem, foram utilizados predominantemente componentes SMD (Surface Mount Device), que oferecem melhor performance e menor ocupação de espaço. A soldagem foi realizada com uma estação de soldagem a ar quente profissional, equipada com controle preciso de temperatura e fluxo de ar. A pasta de solda utilizada foi selecionada conforme especificações técnicas para garantir boas propriedades mecânicas e elétricas da junção. Foram adotadas técnicas padronizadas de montagem para garantir consistência.

Os testes elétricos foram realizados utilizando equipamentos especializados como multímetros digitais de alta precisão e osciloscópios. Foi verificada a continuidade entre os pontos críticos da placa, bem como a ausência de curtos-circuitos indesejados. A equipe realizou medições de tensão em todos os pontos de alimentação e verificou a integridade das conexões. Os resultados foram documentados e comparados com os valores teóricos esperados. Foram executados também testes funcionais em condições normais de operação.

Na fase final, foram realizadas validações adicionais incluindo testes de funcionamento em temperatura ambiente controlada e análises de ruído eletromagnético. A equipe implementou um protocolo sistemático de verificação que contemplou todos os aspectos críticos do projeto. Os resultados obtidos foram documentados em relatórios técnicos detalhados, permitindo o acompanhamento futuro do comportamento da placa. Foram também elaborados procedimentos para manutenção preventiva e corretiva.

## 2.1.4. Qual a aprendizagem com a atividade

Esta experiência proporcionou um aprendizado profundo sobre a importância fundamental do design adequado em projetos de hardware embarcado. A equipe adquiriu conhecimento prático sobre a seleção criteriosa de componentes e suas implicações no desempenho final do sistema. A experiência prática com soldagem de componentes SMD permitiu desenvolver habilidades técnicas específicas, além de compreender a importância da qualidade na execução desta etapa. Os testes realizados demonstraram a relevância da validação sistemática em cada fase do desenvolvimento.

Durante o processo, foi possível observar a relação direta entre o planejamento inicial e o sucesso final do projeto. A equipe aprendeu a valorizar a documentação detalhada e a metodologia sistemática no desenvolvimento de hardware. A experiência reforçou a necessidade de considerar múltiplos aspectos simultaneamente, desde a compatibilidade entre componentes até a facilidade de manutenção futura. O trabalho em equipe permitiu compartilhar conhecimentos específicos de cada área envolvida.

Os desafios encontrados durante o processo serviram como oportunidades de aprendizado significativas. A necessidade de resolver problemas técnicos específicos estimulou a criatividade e o pensamento crítico. A experiência prática com equipamentos especializados ampliou o conhecimento sobre ferramentas de medição e teste. A equipe desenvolveu uma maior compreensão sobre a importância da qualidade e precisão em cada etapa do desenvolvimento de hardware embarcado. Os resultados obtidos demonstraram a eficácia da metodologia adotada.

#2.2. Desenvolvimento de Firmware para a ECU
## 2.2.1. O que foi feito

O desenvolvimento do firmware para a ECU foi realizado utilizando o microcontrolador STM32G0, com implementação completa do código fonte sem dependência de bibliotecas de fornecedor. O projeto foi compilado utilizando o kit de ferramentas GCC da ARM, permitindo um controle total sobre o código gerado. A implementação focou na criação de código proprietário, garantindo a propriedade intelectual do produto. O desenvolvimento abrangeu desde a programação dos periféricos básicos até a implementação de protocolos de comunicação avançados. A equipe manteve um controle rigoroso sobre cada linha de código desenvolvida.

A arquitetura do sistema foi projetada considerando a modularidade e escalabilidade, permitindo futuras expansões e manutenções. O código foi estruturado em módulos independentes, facilitando a manutenção e atualizações futuras. Foram implementados mecanismos de tratamento de erros robustos e sistemas de logging para diagnóstico. A equipe adotou práticas de programação defensiva em todas as rotinas desenvolvidas.

O desenvolvimento incluiu a implementação de rotinas de inicialização do sistema, gerenciamento de memória e tratamento de interrupções. Foram criados mecanismos de proteção contra falhas e recuperação de erros, garantindo a robustez do sistema. A equipe implementou também sistemas de monitoramento de recursos e controle de tempo real. Todas as funcionalidades foram documentadas detalhadamente para facilitar a manutenção futura.

## 2.2.2. Por que foi feito

A decisão de desenvolver o firmware sem utilizar bibliotecas do fornecedor foi estratégica, visando aumentar a propriedade intelectual do produto e reduzir dependências externas. Esta abordagem permitiu um controle total sobre o código desenvolvido, eliminando riscos associados a licenças de terceiros. A equipe pôde otimizar o código conforme as necessidades específicas do projeto, resultando em melhor performance e menor consumo de recursos.

A implementação própria dos drivers permitiu uma maior flexibilidade e customização, adaptando-se perfeitamente às necessidades específicas da ECU. A equipe pôde otimizar cada rotina considerando os requisitos exatos do sistema, resultando em melhor eficiência energética e desempenho. Esta abordagem também facilitou a manutenção e atualizações futuras, pois não há dependência de atualizações de terceiros.

A escolha desta metodologia permitiu também o desenvolvimento de funcionalidades específicas que não estariam disponíveis em bibliotecas padrão. A equipe pôde implementar otimizações específicas para o hardware utilizado e criar soluções personalizadas para os desafios encontrados. Esta abordagem resultou em um produto mais robusto e adaptado às necessidades específicas da aplicação.

## 2.2.3. Como foi feito

O desenvolvimento iniciou com um estudo aprofundado da arquitetura do STM32G0, focando em suas capacidades e limitações. A equipe realizou uma análise detalhada dos recursos disponíveis, incluindo memória, periféricos e capacidades de processamento. Esta fase inicial foi fundamental para definir a melhor abordagem para cada funcionalidade do sistema.

A implementação dos drivers foi realizada de forma sistemática, começando pelos periféricos básicos como GPIO e ADC, até os protocolos de comunicação mais complexos como CAN e I2C. Cada driver foi desenvolvido considerando a otimização de recursos e a robustez do sistema. Foram implementados mecanismos de buffer circular para tratamento eficiente de dados e sistemas de priorização de tarefas.

Os testes foram realizados em múltiplas etapas, começando com testes unitários de cada driver até a integração completa do sistema. A equipe implementou um framework de testes automatizado para validação contínua do código. Foram realizados testes de estresse e validação em condições extremas de operação, garantindo a robustez do sistema.

A otimização do código foi realizada em várias etapas, focando na redução do consumo de memória e melhoria da performance. Foram implementadas técnicas avançadas de programação, como uso de registradores e otimização de loops críticos. A equipe utilizou ferramentas especializadas para análise de performance e identificação de gargalos.

A fase final incluiu a validação completa do sistema, com testes de campo e verificação de todos os requisitos funcionais. Foram realizados testes de compatibilidade com diferentes versões de hardware e validação de todos os protocolos de comunicação implementados. A documentação técnica foi atualizada com todas as especificações finais do sistema.

## 2.2.4. Qual a aprendizagem com a atividade

O desenvolvimento do firmware proporcionou um aprendizado profundo sobre a arquitetura do STM32G0 e suas capacidades. A equipe adquiriu experiência prática em programação de baixo nível e desenvolvimento de drivers personalizados. A implementação de protocolos de comunicação avançados permitiu um entendimento mais profundo sobre sistemas embarcados e suas interações.

A experiência com testes de unidade e integração reforçou a importância da qualidade do código e da robustez do sistema. A equipe aprendeu técnicas avançadas de depuração e validação de sistemas embarcados. A otimização do código permitiu entender melhor o impacto das decisões de design no desempenho final do sistema.

O projeto demonstrou a importância do planejamento e da organização no desenvolvimento de sistemas complexos. A equipe aprendeu a trabalhar com prazos e a gerenciar a complexidade do código. A documentação do processo e dos resultados foi fundamental para o aprendizado e para a manutenção futura do sistema. A experiência prática com hardware real permitiu uma compreensão mais completa dos conceitos teóricos estudados.





